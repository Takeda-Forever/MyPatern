#include <iostream>
#include <memory>
#include <string>

namespace mySpace
{
	enum : bool {
		DEFAULT_AUTO_RESIZE = 0,
		DEFAULT_VFX = 0,
	};

	class Application
	{
		std::string title;

		class Window
		{
		public:
			int width, height;
			Window(int w, int h) : width(w), height(h) {}
		};

		class Audio
		{
		public:
			int volume = NULL;
			Audio(int _volume = 50) : volume(_volume) {}
		};

		class Video : public Window
		{
			enum Level
			{
				AUTO,
				LOW,
				MEDIUM,
				HIGH,
				ULTRA
			};

			struct Graph
			{
				bool vfx = DEFAULT_VFX;
				bool auto_resize = DEFAULT_AUTO_RESIZE;
				int texture = Level::AUTO;
				int shadow = Level::AUTO;
			} graphics;

		public:
			Video(int w = 800, int h = 600) : Window(w, h) {}
			Window* getWindow() { return this; }
		};

		class Options
		{
			std::unique_ptr<Audio> aud;
			std::unique_ptr<Video> vid;

		public:
			Options& setSound(int volume)
			{
				aud = std::make_unique<Audio>(volume);
				return *this;
			}

			Options& setWindow(int w, int h)
			{
				vid = std::make_unique<Video>(w, h);
				return *this;
			}
			Options() = default;
			Window* getWindow()
			{
				if (vid) {
					return vid->getWindow();
				}
				throw std::runtime_error("Video is not initialized.");
			}
		};

		std::unique_ptr<Options> op;

	public:
		Application& operator()(const std::string& _title)
		{
			title = _title;
			op = std::make_unique<Options>();
			return *this;
		}

		bool isInit()
		{
			if (!op)
			{
				return false;
			}
			return true;
		}

		Options& getOption()
		{
			if (!isInit())
			{
				throw std::runtime_error("Options are not initialized.");
			}
			return *op;
		}

		int getWindowWidth()
		{
			return getOption().getWindow()->width;
		}

		int getWindowHeight()
		{
			return getOption().getWindow()->height;
		}
	};

	Application app;
}

int main()
{
	mySpace::app("MOUSE");
	std::cout << "Window height: " << mySpace::app.getWindowHeight() << std::endl;
	std::cout << "Window width: " << mySpace::app.getWindowWidth() << std::endl;
	return EXIT_SUCCESS;
}
