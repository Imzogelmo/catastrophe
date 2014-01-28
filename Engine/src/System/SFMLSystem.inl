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

#include "System/SFMLSystem.h"
#include "Input/Input.h"

// we only link to static libs on windows.
#if defined (WIN32) || defined (_WIN32)
	#define SFML_STATIC
#endif

#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )

	// Link againt standard SFML libraries.
	#ifdef CE_DEBUG
		#pragma comment ( lib, "sfml-system-s.lib" )
		#pragma comment ( lib, "sfml-window-s.lib" )
	#else
		#pragma comment ( lib, "sfml-system-s.lib" )
		#pragma comment ( lib, "sfml-window-s.lib" )
	#endif
#endif


CE_NAMESPACE_BEGIN


bool SFMLSystem::InternalInit()
{
	return true;
}


void SFMLSystem::InternalTerminate()
{
}


void SFMLSystem::Sleep(int milliseconds)
{
	sf::sleep( sf::milliseconds(milliseconds) );
}



// Window

SFMLWindow::SFMLWindow() :
	Window(),
	m_window(0)
{
}


SFMLWindow::~SFMLWindow()
{
	Close();
	if(m_window)
		delete m_window;
}


double SFMLWindow::GetTime() const
{
	return 0.0;
}


Point SFMLWindow::GetSize() const
{
	sf::Vector2u size = m_window->getSize();
	return Point(size.x, size.y);
}


Point SFMLWindow::GetPosition() const
{
	sf::Vector2u pos = m_window->getSize();
	return Point(pos.x, pos.y);
}


void SFMLWindow::SetVSync( bool vsync )
{
	m_window->setVerticalSyncEnabled(vsync);
}


void SFMLWindow::SetTitle( const fc::string& title )
{
	m_window->setTitle(title.c_str());
}


void SFMLWindow::SetSize( int x, int y )
{
	m_window->setSize( sf::Vector2u(x, y) );
	m_size = GetSize();
}


void SFMLWindow::SetPosition( const Point& pos )
{ 
	m_window->setPosition( sf::Vector2i(pos.x, pos.y) );
	m_position = GetPosition();
}


void SFMLWindow::Iconify()
{
}


void SFMLWindow::Restore()
{
}


bool SFMLWindow::IsActive() const
{
    return true;
}


void SFMLWindow::SetCursorVisible(bool visible)
{
	m_window->setMouseCursorVisible(visible);
}


void SFMLWindow::SwapBuffers()
{
	m_window->display();
}


bool SFMLWindow::HasFocus() const
{
	return m_hasFocus;
}


bool SFMLWindow::Open(int w, int h, bool fullscreen, bool resizable,
	int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	size_t screenWidth		= (size_t)w;
	size_t screenHeight		= (size_t)h;
	size_t depthBits		= (size_t)depth_buffer_bits;
	size_t stencilBits		= (size_t)stencil_bits;
	size_t antialiasLevel	= (size_t)multisample_level;
	size_t windowStyle		= fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	if( !m_window )
	{
		m_window = new sf::Window();
	}
	else
	{
		m_window->close();
	}

	m_window->create(
		sf::VideoMode( screenWidth, screenHeight, 32 ),
		m_title.c_str(),
		windowStyle,
		sf::ContextSettings( depthBits, stencilBits, antialiasLevel, 2, 1 )
	);

	if(!m_window->isOpen())
	{
		//fullscreen is probably the lowest common denominator here
		if(fullscreen)
		{
			fullscreen = false;
			return Open(w, h, fullscreen, resizable, depth_buffer_bits, stencil_bits, multisample_level);
		}

		return false;
	}

	// we don't want key repeat.
	m_window->setKeyRepeatEnabled(false);

	m_position = GetPosition();
	m_size = GetSize();
	m_depth_bits	= m_window->getSettings().depthBits;
	m_isOpen		= m_window->isOpen();
	m_hasFocus		= m_isOpen;

	// set up default opengl states
	InternalResize(m_size);
	SetOrthographicProjection();
	SetDefaultOpenGLState();

	return true;
}


void SFMLWindow::Close()
{
	m_window->close();
	m_isOpen = false;
}


Point SFMLWindow::GetDesktopSize() const
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	return Point(desktop.width, desktop.height);
}


void SFMLWindow::Update()
{
	sf::Event event;

	while(m_window->pollEvent(event))
	{
		switch( event.type )
		{
			case sf::Event::Closed:
			{
				SetRequestClose(true);
				break;
			}

			case sf::Event::Resized:
			{
				SetSize(event.size.width, event.size.height);
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

			case sf::Event::KeyPressed:
			{
				Input::GetKeyboard()->SetKeyPress(event.key.code);
				break;
			}

			case sf::Event::KeyReleased:
			{
				Input::GetKeyboard()->SetKeyRelease(event.key.code);
				break;
			}

			case sf::Event::MouseWheelMoved:
			{
				Mouse* mouse = Input::GetMouse();
				mouse->SetWheelPos( mouse->GetWheel() + event.mouseWheel.delta );
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				Input::GetMouse()->SetButton(event.mouseButton.button, true);
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				Input::GetMouse()->SetButton(event.mouseButton.button, false);
				break;
			}

			case sf::Event::MouseMoved:
			{
				Input::GetMouse()->SetPos( Point(event.mouseMove.x, event.mouseMove.y) );
				break;
			}

			//don't really care about the rest.
			default:
				break;
		}

		if( !m_hasFocus )
		{
			//sf::Sleep( 1.f / 60.f ); //one frame
			//todo: need to repaint..
		}
	}
}



/////////////////////////////////////
//         Joystick
/////////////////////////////////////

void Joystick::Update()
{
	for( int i(0); i < 2; ++i )
	{
		m_previous_analog[i] = m_analog[i];

		const int axis = (i * 2);
		m_analog[i].x = sf::Joystick::getAxisPosition(m_joyNumber, (sf::Joystick::Axis)(axis)) / 100.f;
		m_analog[i].y = sf::Joystick::getAxisPosition(m_joyNumber, (sf::Joystick::Axis)(axis + 1)) / 100.f;
	}

	for( uint i(0); i < MaxButtons; ++i )
	{
		if( sf::Joystick::isButtonPressed(m_joyNumber, i) )
		{
			m_button[ i ]++;
			m_buttonReleaseFlags &= ~(1 << i);
		}
		else
		{
			if( m_button[i] != 0 )
			{
				m_button[i] = 0;
				m_buttonReleaseFlags |= (1 << i);
			}
		}
	}

	float povX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	float povY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

	enum _Pov_Directions 
	{
		POV_UP = 0x01, POV_RIGHT = 0x02, POV_DOWN = 0x04, POV_LEFT = 0x08
	};

	m_pov = (0x00000000);
	if( povX < 0.f ) m_pov |= POV_LEFT;
	else if( povX > 0.f ) m_pov |= POV_RIGHT;
	if( povY < 0.f ) m_pov |= POV_UP;
	else if( povY > 0.f ) m_pov |= POV_DOWN;

}

/*
void Mouse::Poll( const void* const* mouseInput, int wheelParam )
{
	const sf::Input* mouse = (sf::Input*)*mouseInput;

	m_previous = m_pos;
	m_pos.x = mouse->GetMouseX();
	m_pos.y = mouse->GetMouseY();

	for( int i(0); i < MaxMouseButtons; ++i )
		m_button[ i ] =  mouse->IsMouseButtonDown( (sf::Mouse::Button) i );

	m_wheel = wheelParam;
}
*/


CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


#endif //CE_SFML



