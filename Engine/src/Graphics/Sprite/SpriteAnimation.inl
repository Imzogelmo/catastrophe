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
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/Sprite/SpriteAnimation.h"

CE_NAMESPACE_BEGIN


SpriteAnimation::SpriteAnimation() :
	frameCounter(0.f),
	frameSpeed(10.f),
	currentFrame(0),
	numFrames(1),
	frameOffsetX(32),
	frameOffsetY(32),
	animationType(0),
	animationFlags(0)
{
}


SpriteAnimation::SpriteAnimation(AnimationType type, float animationFrameDelay, u16 numberOfFrames) :
	frameCounter(0.f),
	frameSpeed(10.f),
	currentFrame(0),
	numFrames(1),
	frameOffsetX(32),
	frameOffsetY(32),
	animationType(0),
	animationFlags(0)
{
	SetAnimationData(type, animationFrameDelay, numberOfFrames);
}


void SpriteAnimation::SetAnimationData(AnimationType type, float animationFrameDelay, u16 numberOfFrames)
{
	SetAnimationType(type);
	SetNumFrames(numberOfFrames);
	SetAnimationSpeedFrames(animationFrameDelay);
}


void SpriteAnimation::SetNumFrames(u16 value)
{
	numFrames = numFrames ? value : 1;
	if(currentFrame >= numFrames)
		currentFrame = 0;
}


void SpriteAnimation::SetCurrentFrame(u16 index, Texture* texture, const PackedRect& sourceRectangle, Rectf& uv)
{
	if(index < numFrames)
	{
		currentFrame = index;

		if(texture != null)
		{
			int x = sourceRectangle.position.x + (frameOffsetX * currentFrame);
			int yOffset = x / texture->Width();

			// If the row is the same, calculation of top, bottom uv will be the same also.
			if(yOffset > 0)
			{
				x %= texture->Width();

				int y = sourceRectangle.position.y + (frameOffsetY * yOffset);
				float texHeightf = texture->Heightf();

				uv.min.y = y / texHeightf;
				uv.max.y = (y + sourceRectangle.size.y) / texHeightf;
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


void SpriteAnimation::Update(Texture* texture, const PackedRect& sourceRect, Rectf& uv)
{
	if(numFrames > 1 && !GetPaused())
	{
		++frameCounter;

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

			SetCurrentFrame(currentFrame, texture, sourceRect, uv);
		}
	}
}


void SpriteAnimation::SetFlipX(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_FlipX;
	else
		animationFlags &= ~AnimationFlags_FlipX;
}


void SpriteAnimation::SetFlipY(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_FlipY;
	else
		animationFlags &= ~AnimationFlags_FlipY;
}


void SpriteAnimation::SetPaused(bool value)
{
	if(value)
		animationFlags |= AnimationFlags_Pause;
	else
		animationFlags &= ~AnimationFlags_Pause;
}


void SpriteAnimation::SetAnimationType(AnimationType type)
{
	animationType = (u8)type;
}


bool SpriteAnimation::IsAnimationFinished() const
{
	return (animationType == AnimationType_OneTime &&
	        currentFrame == (numFrames - 1) &&
	        frameCounter >= frameSpeed);
}


float SpriteAnimation::GetAnimationLengthFrames() const
{
	if(animationType != (u8)AnimationType_PingPong)
	{
		return (float)(frameSpeed * numFrames);
	}

	return (frameSpeed * (float)((numFrames * 2) - 1));
}


float SpriteAnimation::GetAnimationLengthSeconds() const
{
	// Seconds = [frames * (1 / 60.f)].
	// If in the future FPS is not 60 then this would need to be changed.

	return (float)GetAnimationLengthFrames() * 0.016666667f;
}



CE_NAMESPACE_END
