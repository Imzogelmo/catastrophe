// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Graphics/Sprite/PackedSpriteAnimation.h"
#include "Catastrophe/Graphics/Texture.h"

CE_NAMESPACE_BEGIN


PackedSpriteAnimation::PackedSpriteAnimation() :
	frameCounter(0),
	frameSpeed(16),
	currentFrame(0),
	numFrames(1),
	animationType(0),
	animationFlags(0)
{
}


PackedSpriteAnimation::PackedSpriteAnimation(AnimationType type, u16 animationFrameDelay, u8 numberOfFrames) :
	frameCounter(0),
	frameSpeed(16),
	currentFrame(0),
	numFrames(1),
	animationType(0),
	animationFlags(0)
{
	SetAnimationData(type, animationFrameDelay, numberOfFrames);
}


void PackedSpriteAnimation::SetAnimationData(AnimationType type, u16 animationFrameDelay, u8 numberOfFrames)
{
	SetAnimationType(type);
	SetNumFrames(numberOfFrames);
	SetAnimationSpeedFrames(animationFrameDelay);
}


void PackedSpriteAnimation::SetNumFrames(u16 value)
{
	numFrames = numFrames ? value : 1;
	if(currentFrame >= numFrames)
		currentFrame = 0;
}


void PackedSpriteAnimation::SetCurrentFrame(u8 index, Texture* texture, const PackedRect& sourceRectangle, Rectf& uv)
{
	if(index < numFrames)
	{
		currentFrame = index;

		if(texture != null)
		{
			int positionX = (int)sourceRectangle.position.x;
			int positionY = (int)sourceRectangle.position.y;
			int sizeX = (int)sourceRectangle.size.x;
			int sizeY = (int)sourceRectangle.size.y;

			int x = positionX + (sizeX * currentFrame);
			int yOffset = x / texture->Width();

			// If the row is the same, calculation of top, bottom uv will be the same also.
			if(yOffset > 0)
			{
				x %= texture->Width();

				int y = positionY + (sizeY * yOffset);
				float texHeightf = texture->Heightf();

				uv.min.y = y / texHeightf;
				uv.max.y = (y + sizeY) / texHeightf;
			}

			float texWidthf = texture->Widthf();

			uv.min.x = x / texWidthf;
			uv.max.x = (x + sourceRectangle.size.x) / texWidthf;

			// FlipX
			if(animationFlags & AnimationFlags_FlipX)
				Swap(uv.min.x, uv.max.x);

			// FlipY
			if(animationFlags & AnimationFlags_FlipY)
				Swap(uv.min.y, uv.max.y);

		}
	}
}


void PackedSpriteAnimation::Update(Texture* texture, const PackedRect& sourceRectangle, Rectf& uv)
{
	if(numFrames > 1 && !GetPaused())
	{
		frameCounter += 16;
		if(frameCounter >= frameSpeed)
		{
			frameCounter -= frameSpeed;

			// Loop animation
			if(animationType == AnimationType_Loop)
			{
				currentFrame = (currentFrame + 1) % numFrames;
			}

			// One time animation
			else if(animationType == AnimationType_OneTime)
			{
				if(currentFrame == numFrames - 1)
					return;

				++currentFrame;
			}

			// Ping-pong animation
			else // AnimationType_PingPong
			{
				// Backwards
				if((animationFlags & AnimationFlags_Reverse) != 0)
				{
					if(currentFrame == 0)
					{
						++currentFrame;
						animationFlags ^= AnimationFlags_Reverse;
					}
					else
						--currentFrame;
				}

				// Forwards
				else
				{
					if(currentFrame == numFrames - 1)
					{
						--currentFrame;
						animationFlags |= AnimationFlags_Reverse;
					}
					else
						++currentFrame;

				}
			}

			SetCurrentFrame(currentFrame, texture, sourceRectangle, uv);
		}
	}
}


void PackedSpriteAnimation::SetFlipX(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_FlipX;
	else
		animationFlags &= ~AnimationFlags_FlipX;
}


void PackedSpriteAnimation::SetFlipY(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_FlipY;
	else
		animationFlags &= ~AnimationFlags_FlipY;
}


void PackedSpriteAnimation::SetPaused(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_Pause;
	else
		animationFlags &= ~AnimationFlags_Pause;
}


bool PackedSpriteAnimation::IsAnimationFinished() const
{
	return (animationType == AnimationType_OneTime &&
	        currentFrame == (numFrames - 1) &&
	        frameCounter >= frameSpeed);
}


int PackedSpriteAnimation::GetAnimationLengthRaw() const
{
	if(animationType != (u8)AnimationType_PingPong)
	{
		return (int)(frameSpeed * numFrames);
	}

	return (int)(frameSpeed * ((numFrames * 2) - 1));
}


int PackedSpriteAnimation::GetAnimationLengthFrames() const
{
	return GetAnimationLengthRaw() / 16;
}


float PackedSpriteAnimation::GetAnimationLengthSeconds() const
{
	// The following are equivelent:
	// [raw / 16 / 60FPS] = [raw * 0.0625f * 0.016666667f] = [raw * 0.0010416667f].
	// If in the future FPS is not 60 then this would need to be changed.

	return (float)GetAnimationLengthRaw() * 0.0010416667f;
}



CE_NAMESPACE_END
