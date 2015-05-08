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

#include "Graphics/PackedSprite.h"
#include "Graphics/Texture.h"

CE_NAMESPACE_BEGIN


PackedSprite::PackedSprite() :
	texture(0),
	size(Vector2::Zero),
	angle(0.f),
	color(Color::White()),
	uv(Rectf::Zero),
	sourceRect(PackedRect::Zero),
	frameCounter(0),
	currentFrame(0),
	animationSpeed(16),
	numFrames(1)
{
}


PackedSprite::PackedSprite( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay )
{
	angle = 0.f,
	color = Color::White();
	size = Vector2(sourceRectangle.size);
	frameCounter = 0;
	currentFrame = 0;
	SetTexture(texturePtr);
	Create(sourceRectangle, numberOfFrames, frameDelay);
}


u32 PackedSprite::GetTextureID() const
{
	return texture ? texture->GetTextureID() : 0;
}


void PackedSprite::SetAnimationSpeed( s16 frameDelay )
{
	animationSpeed = Clamp<s16>(frameDelay, 16, 32736);
}


void PackedSprite::SetTexture( Texture* texturePtr )
{
	CE_ASSERT(texturePtr != 0);
	CE_ASSERT(texturePtr->Width() != 0 && texturePtr->Height() != 0);
	texture = texturePtr;
}


void PackedSprite::SetSourceRect( const PackedRect& sourceRectangle )
{
	CE_ASSERT(texture != 0);
	sourceRect = sourceRectangle;
	size = Vector2(sourceRectangle.size); //fixme

	float w = (float)texture->Width();
	float h = (float)texture->Height();
	uv.min.x = (float)sourceRectangle.Left() / w;
	uv.max.x = (float)sourceRectangle.Right() / w;
	uv.min.y = (float)sourceRectangle.Top() / h;
	uv.max.y = (float)sourceRectangle.Bottom() / h;

	if( currentFrame > 0 )
	{
		SetCurrentFrame(currentFrame);
	}
}


void PackedSprite::Update()
{
	if( numFrames > 1 )
	{
		// animation speed is fixed point 16 : 1. this means
		// that one second (60 frames) is equal to 960 fixed point.
		// therefore the longest animation delay we can have is
		// 34 seconds (2167 - 16 = 2151 frames).

		frameCounter += 16;
		if( frameCounter >= animationSpeed )
		{
			frameCounter -= animationSpeed;
			if( ++currentFrame >= numFrames )
			{
				currentFrame -= numFrames;
			}

			// only update our uv coords
			SetCurrentFrame(currentFrame);
		}
	}
}


void PackedSprite::SetCurrentFrame( s16 index )
{
	// texture must be assigned first.
	CE_ASSERT(texture != 0);

	if( index < numFrames )
	{
		currentFrame = index;

		//float w = (float)texture->Width();
		//float h = (float)texture->Height();
		int w = (int)sourceRect.Width();
		int x = (int)sourceRect.position.x + (w * (int)currentFrame);
		int yOffset = x / texture->Width();
		if( yOffset > 0 )
		{
			x %= texture->Width();

			int h = (int)sourceRect.Height();
			int y = (int)sourceRect.position.y + (h * yOffset);
			float texHeightf = (float)texture->Width();
			uv.min.y = y / texHeightf;
			uv.max.y = (y + h) / texHeightf;
		}

		float texWidthf = (float)texture->Width();
		uv.min.x = x / texWidthf;
		uv.max.x = (x + w) / texWidthf;
	}
}


void PackedSprite::Create( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay )
{
	SetTexture(texturePtr);
	Create(sourceRectangle, numberOfFrames, frameDelay);
}


void PackedSprite::Create( const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay )
{
	numFrames = (s16)(numberOfFrames > 0 ? numberOfFrames : 1);

	SetAnimationSpeed(frameDelay);
	SetSourceRect(sourceRectangle);
	//SetCurrentFrame(current_frame);
}



CE_NAMESPACE_END
