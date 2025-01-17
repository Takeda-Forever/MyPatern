```cpp
namespace mySpace
{
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
			enum Level;
			struct Graph{
			}graphics;
		public:
			Video(int w = 800, int h = 600) : Window(w, h) {}
			Window* getWindow() { return this; }
		};

		class Options
		{
			std::unique_ptr<Audio> aud;
			std::unique_ptr<Video> vid;
		public:
			Options& setSound(int volume);
			Options& setWindow(int w, int h)l;
			Options() = default;
			Window* getWindow();
		};

		std::unique_ptr<Options> op;
		bool isInit();

	public:
		Application& operator()(const std::string& _title);
		Options& getOption();

		int getWindowWidth();
		int getWindowHeight();
	};

	Application app;
}
```
```cpp
int main()
{
	mySpace::app("MOUSE").getOption().setWindow(1280, 800).setSound(80);
	std::cout << "Window height: " << mySpace::app.getWindowHeight() << std::endl;
	std::cout << "Window width: " << mySpace::app.getWindowWidth() << std::endl;
	return EXIT_SUCCESS;
}
```

## Description:
How's look my patern: 
>namespace MySpace:
>class Application:
>
>	class Window;
>
>	class Video <- Window;
>
>	class Audio;
>
>	class Options <- Video, Audio;


The `Application` class acts as the core of the program, providing access to window and settings management. Key features include:
- An overloaded `operator()` for initialization, which returns a pointer to an `Options` object for further configuration.
- `getWindowWidth()` and `getWindowHeight()` methods to retrieve the dimensions of the window.

The `Options` class allows control over audio and video parameters, enabling customization of application behavior. It interacts directly with the `Audio` and `Video` classes.

The `Video` class, a critical component for graphics control, includes the `getWindow()` method, which returns a pointer to itself. This method provides access to graphical settings, including textures, shadows, and resolution.

In summary, this design enables centralized management of audio, video, and application settings, ensuring flexibility and modularity for further development.


