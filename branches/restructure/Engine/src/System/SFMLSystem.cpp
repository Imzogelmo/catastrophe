// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
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


#ifdef CE_SFML

#include <SFML/Window.hpp>


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


SFMLSystem::~SFMLSystem()
{
	if(m_window)
		delete m_window;
}

void SFMLSystem::CloseWindow()
{
	if(m_window && m_window->IsOpen())
		m_window->Close();
}

double SFMLSystem::GetTime()
{
	return 0.0;
}

void SFMLSystem::SetWindowTitle(const char* title)
{
	m_window->SetWindowTitle(title);
}

void SFMLSystem::SetWindowSize(const Point& size)
{
	m_window->SetSize( (uint)size.x, (uint)size.y );
}

Point SFMLSystem::GetWindowSize()
{
	return m_windowSize;
}

void SFMLSystem::Sleep(int milliseconds)
{
	sf::Sleep((float)milliseconds);
}

void SFMLSystem::Iconify()
{
}

void SFMLSystem::Restore()
{
}

void SFMLSystem::SetCursorVisible(bool visible)
{
}

void SFMLSystem::Update()
{
	sfmlProcessEvents();
}

void SFMLSystem::SwapBuffers()
{
	m_window->SwapBuffers();
}

bool SFMLSystem::HasFocus() const
{
	return m_hasFocus;
}


bool SFMLSystem::CreateWindow(const Point& size, bool fullscreen, bool resizable,
		const Color& bits, int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	const char* windowTitle	= "Game";
	uint screenWidth	= (uint)size.x;
	uint screenHeight	= (uint)size.y;
	uint colorDepth		= (uint)((bits.r + bits.g + bits.b + bits.a) > 16 ? 32 : 16);
	uint depthBits		= (uint)depth_buffer_bits;
	uint stencilBits	= (uint)stencil_bits;
	uint antialiasLevel = (uint)multisample_level; //"antialias" is actually multisample.

	unsigned long windowStyle = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	if( !m_window )
	{
		m_window = new sf::Window();
	}
	else
	{
		m_window->Close();
	}

	m_window->Create(
		sf::VideoMode( screenWidth, screenHeight, colorDepth ),
		windowTitle, windowStyle,
		sf::ContextSettings( depthBits, stencilBits, antialiasLevel, 2, 0 )
	);

	if(!m_window->IsOpened())
	{
		//fullscreen is probably the lowest common denominator here
		if(fullscreen)
		{
			fullscreen = false;
			return CreateWindow(size, fullscreen, resizable, bits, depth_buffer_bits, stencil_bits, multisample_level);
		}

		return false;
	}

	return true;
}


void SFMLSystem::sfmlProcessEvents()
{
	sf::Event event;

	while(m_window->GetEvent(event))
	{
		switch( event.Type )
		{
			case sf::Event::Closed:
			{
				postQuitMessage = true;
				break;
			}
			case sf::Event::Resized:
			{
				ResizeWindow( Point(event.Size.Width, event.Size.Height) );
				break;
			}
			case sf::Event::LostFocus:
			{
				m_hasFocus = false;
				break;
			}
			case sf::Event::GainedFocus:
			{
				m_hasFocus = true;
				break;
			}

			//Key released events
			case sf::Event::KeyReleased:
			{
				Input::SetKeyReleased(event.Key.Code);
				break;
			}
			//Key pressed events
			case sf::Event::KeyPressed:
			{
				Input::SetKeyPressed(event.Key.Code);

				switch( event.Key.Code )
				{
					// Esc: exit fullscreen
					case sf::Key::Escape:
					{
						postQuitMessage = true;
						break;
					}
					default:
						break;
				}
				break;
			}

			//don't really care about the rest.
			default:
				break;
		}

		if( !m_hasFocus )
		{
			sf::Sleep( 1.f / 60.f ); //one frame
			//todo: need to repaint..
		}

		if( postQuitMessage )
		{
			//request to exit the application granted.
			return;
		}
	}
}


void SFMLSystem::sfmlPollJoystick()
{
	const sf::Input * joy = (sf::Input*)*joystickInput;

	for( int i(0); i < 3; ++i )
	{
		_previous_analog[ i ] = _analog[ i ];

		const int axis = (i * 2);
		_analog[ i ].x = (joy->GetJoystickAxis( _joyNumber, (sf::Joy::Axis)(axis    ) ) / 100.f);
		_analog[ i ].y = (joy->GetJoystickAxis( _joyNumber, (sf::Joy::Axis)(axis + 1) ) / 100.f);
	}

	for( uint i(0); i < 12; ++i )
	{
		if( joy->IsJoystickButtonDown( _joyNumber, i ) )
		{
			_button[ i ]++;
			_buttonReleaseFlags &= ~( (uint)(1 << i) );
		}
		else
		{
			if( _button[ i ] != 0 )
			{
				_button[ i ] = 0;
				_buttonReleaseFlags |= ( (uint)(1 << i) );
			}
		}
	}

	_pov = (0x00000000);
	const int joyPov = (int) joy->GetJoystickAxis( _joyNumber, sf::Joy::AxisPOV );

	enum _Pov_Directions 
	{
		_Up = 0x01, _Right = 0x02, _Down = 0x04, _Left = 0x08
	};

	if( joyPov > 270 || joyPov <  90 )	_pov |= _Up;
	if( joyPov >   0 && joyPov < 180 )	_pov |= _Right;
	if( joyPov >  90 && joyPov < 270 )	_pov |= _Down;
	if( joyPov > 180 )					_pov |= _Left;

}

void Mouse::Poll( const void* const* mouseInput, int wheelParam )
{
	const sf::Input* mouse = (sf::Input*)*mouseInput;

	_previous = _pos;
	_pos.x = mouse->GetMouseX();
	_pos.y = mouse->GetMouseY();

	for( int i(0); i < MaxMouseButtons; ++i )
		_button[ i ] =  mouse->IsMouseButtonDown( (sf::Mouse::Button) i );

	_wheel = wheelParam;
}


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


#endif



