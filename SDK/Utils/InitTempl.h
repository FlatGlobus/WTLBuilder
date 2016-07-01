
#ifndef __INITTEMPL_H
#define __INITTEMPL_H
//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, T t> class Init
{
public:
	Init(void):val(t)
	{
	}

	operator T&()
	{
		return val;
	}

	operator T&()const
	{
		return val;
	}

	T& AsType()
	{
		return val;
	}

	const T& AsType() const
	{
		return val;
	}

	T* operator&()
	{
		return &val;
	}

	const T* operator&() const
	{
		return &val;
	}

	T& operator=(const T& t)
	{
		return (val = t);
	}

	Init(const Init& rhs)
	{
		val = rhs.val;
	}

private:
	T val;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
#endif