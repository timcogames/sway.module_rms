# sway.module_rms

#### Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release -DMODULE_RMS_ENABLE_TESTS=ON -DCUSTOM_GTEST_ROOT_DIR=/Users/apriori85/Documents/Third-party/googletest ../
```

#### Запускаем сборку

```console
cmake --build ./
```
