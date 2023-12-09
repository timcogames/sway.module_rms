# sway.module_rms

[![codecov][codecov-svg]][codecov-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest \
      -D MODULE_RMS_ENABLE_TESTS=ON ../
```

#### Запускаем сборку

```console
cmake --build ./
```

[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_rms/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_rms
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_rms.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_rms/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
