<a name="readme-top"></a>

<!-- ABOUT THE PROJECT -->
## What is This?

OBS-C is a small C++ library that leverages the OBS (Open Broadcast Software) graphics-hook to capture any D3D, Vulkan, or OpenGL application safely and efficiently.

It does this by injecting the library into the target (just like OBS would) and then communcating with it in the same manner as OBS itself. Since the software is developed by OBS themselves, you can expect it to support all anti-cheats, be efficient, and of course it's signed.

> Note: This will NOT inject the library manually. It will spawn the injection helper provided along-side OBS and tell it to do so. Again, hopefully bypassing any anti-cheat restrictions.

## Where are the binaries

The library requires you have the following files:
```
get-graphics-offsets32.exe
get-graphics-offsets64.exe

graphics-hook32.dll
graphics-hook64.dll

inject-helper32.exe
inject-helper64.exe
```

These can be obtained by navigating to `%programfiles%\obs-studio\data\obs-plugins\win-capture`. This may of course be different for you. However, the general structure still holds true. You may not need both 32 and 64 bit, if you know the application you're capturing and it's bitness.

Once you have the files, place them alongside exe you make. At application root.

<!-- USAGE EXAMPLES -->
## Usage and Examples

```cpp
#include "obsc/obsc.h"

int main() {
    // Inject the dll into the target process & setup our lines of communication
    obsc::Capture capture("WINDOW NAME HERE");
    capture.attach();

    // Capture a frame from the target process
    auto [frame, size] = capture.captureFrame();
    
    return 0;
}
```

<!-- CONTRIBUTING -->
## Contributing

Any contributions you can make are **super appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Mwah!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- Acknowledgements -->
## Acknowledgements

https://github.com/not-matthias/obs-rs/tree/main
https://github.com/ToruNiina/toml11
https://github.com/fmtlib/fmt

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE](https://github.com/bonezone2001/obsc/blob/master/LICENSE) for more information.
