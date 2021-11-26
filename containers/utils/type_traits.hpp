#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

//#include <type_traits>

namespace ft
{

	template <bool, class T = void>
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class _Tp>
	struct remove_const
	{
		typedef _Tp type;
	};

	template <class _Tp>
	struct remove_const<const _Tp>
	{
		typedef _Tp type;
	};

	template <class _Tp>
	struct remove_volatile
	{
		typedef _Tp type;
	};

	template <class _Tp>
	struct remove_volatile<volatile _Tp>
	{
		typedef _Tp type;
	};

	template <class _Tp>
	struct remove_cv
	{
		typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
	};

	template <class T>
	struct _is_integral
	{
		static const bool value = false;
	};

	template <>
	struct _is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct _is_integral<long long>
	{
		static const bool value = true;
	};

	template <class T>
	struct is_integral : public _is_integral<typename remove_cv<T>::type>
	{};

}

#endif
