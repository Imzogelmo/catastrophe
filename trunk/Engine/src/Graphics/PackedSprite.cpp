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
	source_rect(PackedRect::Zero),
	frame_counter(0),
	current_frame(0),
	anim_speed(16),
	num_frames(1)
{
}


PackedSprite::PackedSprite( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, short frameDelay )
{
	angle = 0.f,
	color = Color::White();
	size = sourceRectangle.size.ToPoint();
	frame_counter = 0;
	current_frame = 0;
	SetTexture(texturePtr);
	SetFrameData(sourceRectangle, numberOfFrames, frameDelay);
}


void PackedSprite::SetAnimationSpeed( short frameDelay )
{
	anim_speed = fc::clamp<short>(frameDelay, 16, 32736);
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
	source_rect = sourceRectangle;
	size = sourceRectangle.size.ToPoint(); //fixme

	float w = (float)texture->Width();
	float h = (float)texture->Height();
	uv.min.x = (float)sourceRectangle.Left() / w;
	uv.max.x = (float)sourceRectangle.Right() / w;
	uv.min.y = (float)sourceRectangle.Top() / h;
	uv.max.y = (float)sourceRectangle.Bottom() / h;

	if( current_frame > 0 )
	{
		SetCurrentFrame(current_frame);
	}
}


void PackedSprite::Update()
{
	if( num_frames > 1 )
	{
		// animation speed is fixed point 16 : 1. this means
		// that one second (60 frames) is equal to 960 fixed point.
		// therefore the longest animation delay we can have is
		// 34 seconds (2167 - 16 = 2151 frames).

		frame_counter += 16;
		if( frame_counter >= anim_speed )
		{
			frame_counter -= anim_speed;
			if( ++current_frame >= num_frames )
			{
				current_frame -= num_frames;
			}

			// only update our uv coords
			SetCurrentFrame(current_frame);
		}
	}
}


void PackedSprite::SetCurrentFrame( short index )
{
	// texture must be assigned first.
	CE_ASSERT(texture != 0);

	if( index < num_frames )
	{
		current_frame = index;

		//float w = (float)texture->Width();
		//float h = (float)texture->Height();
		int w = (int)source_rect.Width();
		int x = (int)source_rect.pos.x + (w * (int)current_frame);
		int yOffset = x / texture->Width();
		if( yOffset > 0 )
		{
			x %= texture->Width();

			int h = (int)source_rect.Height();
			int y = (int)source_rect.pos.y + (h * yOffset);
			float texHeightf = (float)texture->Width();
			uv.min.y = y / texHeightf;
			uv.max.y = (y + h) / texHeightf;
		}

		float texWidthf = (float)texture->Width();
		uv.min.x = x / texWidthf;
		uv.max.x = (x + w) / texWidthf;
	}
}


void PackedSprite::SetFrameData( const PackedRect& sourceRectangle, int numberOfFrames, short frameDelay )
{
	num_frames = (short)(numberOfFrames > 0 ? numberOfFrames : 1);

	SetAnimationSpeed(frameDelay);
	SetSourceRect(sourceRectangle);
	//SetCurrentFrame(current_frame);
}



CE_NAMESPACE_END