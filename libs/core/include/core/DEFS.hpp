// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEFS_HPP__
#define __DEFS_HPP__


#define GD_CORE_LIB_DEBUG // Move to project config
#define GD_WIN_DLL_BUILD  // Move to project config


#if defined(_WIN32) || defined(_WIN64)
  #define GD_WIN_BUILD
#endif


#if defined GD_WIN_BUILD && defined(GD_WIN_DLL_BUILD)
  #define LIB_EXPORT_CONV __declspec(dllexport)
#else
  #define LIB_EXPORT_CONV
#endif


#define BUF_STRIDE( X ) \
    reinterpret_cast<GLvoid*>(X)

#define SAFE_DELETE( PTR ) \
    delete PTR; \
    PTR = nullptr;

#define SAFE_ARR_DELETE( ARR_PTR ) \
    delete[] ARR_PTR; \
    ARR_PTR = nullptr;

#endif /* __DEFS_HPP__ */