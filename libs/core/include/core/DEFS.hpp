// author: Oleksii Zhogan

#ifndef __DEFS_HPP__
#define __DEFS_HPP__

#ifdef GD_WIN_DLL_BUILD
  #define LIB_EXPORT_CONV __declspec(dllexport)
#else
  #define LIB_EXPORT_CONV
#endif

#endif /* __DEFS_HPP__ */