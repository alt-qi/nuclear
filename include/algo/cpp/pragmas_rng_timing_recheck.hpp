/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Прагмы, генератор случайных чисел и замер времени (ГПТ, надо проверить) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

// #pragma GCC optimize("O3")           // Доп. оптимизации и векторизация.
// #pragma GCC optimize("unroll-loops") // Разворачивание подходящих циклов.
// #pragma GCC target("avx2")           // Только если на сервере есть AVX2.

// Прагма действует только на следующий цикл.
#pragma GCC unroll 4
for (int i = 0; i < n; ++i) {
    sum += a[i];
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// a уже считан. Включить таймер при сборке флагом -DLOCAL.
#ifdef LOCAL
const auto start = chrono::steady_clock::now();
#endif

ll sum = 0;
for (int x : a) {
    sum += x;  // Измеряемый код.
}

#ifdef LOCAL
const auto elapsed = chrono::steady_clock::now() - start;
const double ms = chrono::duration<double, milli>(elapsed).count();
cerr << "loop: " << ms << " ms\n";  // Вывод уже вне замера.
#endif
// g++ -DLOCAL main.cpp
/// &TRD_END
