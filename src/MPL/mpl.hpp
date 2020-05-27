#pragma once

namespace Flicker
{
    namespace MPL
    {
        template<typename T>
        void execute_function(T func)
        {
            func();
        }

        template<typename TObject, typename TMethod>
        void execute_method(TObject& object, TMethod method)
        {
            (object.*method)();
        }

        template<typename TObject, typename TMethod, typename TArg>
        void execute_method(TObject& object, TMethod method, TArg arg)
        {
            (object.*method)(arg);
        }

        template<typename TObject, typename TMethod, typename... TArgs>
        void execute_method(TObject& object, TMethod method, TArgs... args)
        {
            (object.*method)(args...);
        }

        template<typename... Ts>
        using Tuple = std::tuple<Ts...>;

        template<typename... Ts>
        struct TypeList
        {
            static constexpr int size {sizeof...(Ts)};
        };

        template<typename, typename>
        struct IndexOf;

        template<typename T, typename... Ts>
        struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<size_t, 0> {};

        template<typename T, typename TOther, typename... Ts>
        struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant<size_t, 1 + IndexOf<T, TypeList<Ts...>>::value> { };

        template<template <typename...>typename TNewName, typename T>
        struct RenameHelper;

        template<template<typename...>typename TNewName, template<typename...> typename TOldName, typename... Ts>
        struct RenameHelper<TNewName, TOldName<Ts...>>
        {
            using type = TNewName<Ts...>;
        };

        template<template<typename...>typename TNewName, typename T>
        using Rename = typename RenameHelper<TNewName, T>::type;

        template<typename, typename>
        struct Contains : std::bool_constant<false> {};

        template<typename T, typename... Ts>
        struct Contains<T, TypeList<T, Ts...>> : std::bool_constant<true> {};

        template<typename T, typename TOther, typename... Ts>
        struct Contains<T, TypeList<TOther, Ts...>> : std::bool_constant<Contains<T, TypeList<Ts...>>::value> {};
    }
}