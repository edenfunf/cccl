//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef _CUDA_STD___TYPE_TRAITS_IS_COMPLETE_H
#define _CUDA_STD___TYPE_TRAITS_IS_COMPLETE_H

#include <cuda/std/detail/__config>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cuda/std/__type_traits/integral_constant.h>

#ifndef _CCCL_BUILTIN_IS_COMPLETE_TYPE
#  include <cuda/std/__type_traits/void_t.h>
#endif

#include <cuda/std/__cccl/prologue.h>

_CCCL_BEGIN_NAMESPACE_CUDA_STD

#ifdef _CCCL_BUILTIN_IS_COMPLETE_TYPE
template <typename T>
struct __is_complete : bool_constant<_CCCL_BUILTIN_IS_COMPLETE_TYPE(T)>
{};
#else
// Must be a SFINAE trait instead of
//
// template <typename T>
// struct is_complete : bool_constant<(sizeof(T) > 0)> {};
//
// Because older NVCC doesn't even allow you to utter the phrase sizeof(T) if T is incomplete
template <typename T, typename = void>
struct __is_complete : false_type
{};

template <typename T>
struct __is_complete<T, void_t<decltype(sizeof(T))>> : bool_constant<(sizeof(T) > 0)>
{};
#endif

template <typename T>
inline constexpr bool __is_complete_v = __is_complete<T>::value;

_CCCL_END_NAMESPACE_CUDA_STD

#undef _CCCL_BUILTIN_IS_COMPLETE_TYPE

#include <cuda/std/__cccl/epilogue.h>

#endif // _CUDA_STD___TYPE_TRAITS_IS_COMPLETE_H
