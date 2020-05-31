#pragma once
#include <type_traits>

namespace mpl
{
    template <typename T>
    void execute_function(T func)
    {
        func();
    }

    template <typename TObject, typename TMethod>
    void execute_method(TObject &object, TMethod method)
    {
        (object.*method)();
    }

    template <typename TObject, typename TMethod, typename TArg>
    void execute_method(TObject &object, TMethod method, TArg arg)
    {
        (object.*method)(arg);
    }

    template <typename TObject, typename TMethod, typename... TArgs>
    void execute_method(TObject &object, TMethod method, TArgs... args)
    {
        (object.*method)(args...);
    }

    template <typename... Ts>
    using Tuple = std::tuple<Ts...>;

    template <typename... Ts>
    struct TypeList
    {
        static constexpr int size{sizeof...(Ts)};
    };

    template <typename, typename>
    struct IndexOf;

    template <typename T, typename... Ts>
    struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<size_t, 0>
    {
    };

    template <typename T, typename TOther, typename... Ts>
    struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant<size_t, 1 + IndexOf<T, TypeList<Ts...>>::value>
    {
    };

    template <template <typename...> typename TNewName, typename T>
    struct RenameHelper;

    template <template <typename...> typename TNewName, template <typename...> typename TOldName, typename... Ts>
    struct RenameHelper<TNewName, TOldName<Ts...>>
    {
        using type = TNewName<Ts...>;
    };

    template <template <typename...> typename TNewName, typename T>
    using Rename = typename RenameHelper<TNewName, T>::type;

    template <typename, typename>
    struct Contains : std::bool_constant<false>
    {
    };

    template <typename T, typename... Ts>
    struct Contains<T, TypeList<T, Ts...>> : std::bool_constant<true>
    {
    };

    template <typename T, typename TOther, typename... Ts>
    struct Contains<T, TypeList<TOther, Ts...>> : std::bool_constant<Contains<T, TypeList<Ts...>>::value>
    {
    };

    template <size_t I, typename TFunc, typename... Ts>
    void for_tuple_impl(Tuple<Ts...>& tuple, TFunc &&func, std::bool_constant<true>)
    {
        func(std::get<I>(tuple));
        for_tuple_impl<I + 1>(tuple, func, std::bool_constant<(I + 1 < TypeList<Ts...>::size)>{});
    }

    template <size_t I, typename TFunc, typename... Ts>
    void for_tuple_impl(Tuple<Ts...>& tuple, TFunc &&func, std::bool_constant<false>)
    {
    }

    template <typename TFunc, typename... Ts>
    void for_tuple(Tuple<Ts...>& tuple, TFunc func)
    {
        for_tuple_impl<0>(tuple, func, std::bool_constant<(0 < TypeList<Ts...>::size)>{});
    }
}