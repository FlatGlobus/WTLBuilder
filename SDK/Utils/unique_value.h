/********************************************************************************************
  File: unique_value.h

  History: Created - 6 May 2001 by LOXmith

  PURPOSE:
    * Defines template for automatic sequential ID numbers. 
    * Useful for implementing IDs. 
    * Supports multiple unique ID categories. 
    * The values are guaranteed to be sequential in each category.

  INTERFACE:
    template <typename TValue, typename TCategory> 
    class unique_value
    {
    public:
        typedef TValue		value_type;
        typedef TCategory	category_type;

        // default constructor
        unique_value(); 

        // cast to value_type operator
        operator const value_type&() const;

        // read acessor for the unique counter
        static const value_type& get_counter();
    		
    protected:
        value_type m_value; //the unique value
    }

    * Use as a numeric datatype in the class you want to have unique IDs. 
    * The category is determined of both TValue and TCategory. 
    * It's reccomended to create a typedef and to use it for all your IDs 
      unless you have a reason not to do so.
    * Use INIT_UNIQUE_CAT and INIT_UNIQUE macros to initialize categories

  EXAMPLE:
	INIT_UNIQUE(long);
	typedef unique_value<long> unique_long;

	class some_data_class
	{
		unique_long ID; // unique for every object
		int data1;
		.......
		int dataN;
	}


    class different_category_data_class;
	INIT_UNIQUE_CAT(long, different_category_data_class);

	class different_category_data_class
	{
	  unique_value<long, different_category_data_class> ID;
	  ....
	}


	foo() 
	{ 
		some_data_class					data_object; 
		different_category_data_class	another_object;
		cout << data_object.ID << another_object.ID; 
	}

/*******************************************************************************************/


#if !defined(__UNIQUE_VALUE__)
#define __UNIQUE_VALUE__

typedef long default_unique_category;

template <typename TValue, typename TCategory=default_unique_category>
class unique_value
{
public:
    typedef TValue		value_type;
    typedef TCategory	category_type;

    unique_value():m_value(m_counter){m_counter++;};        // default constructor
    operator const value_type & () const {return m_value;}; // cast to value_type operator
    operator LPCTSTR(){ sprintf(m_strvalue._T("%u"),m_value); return m_strvalue;}
    // read acessor for the unique counter
    static const value_type& get_counter() {return m_counter;}

protected:
    value_type m_value;				//the unique value
    _TCHAR m_strvalue;

private:
    unique_value   (value_type&);   // FORBIDEN assignment constructor
    void operator= (value_type&);   // FORBIDEN assignment operator

    static value_type m_counter;    // static variable used for unique value generation
};


// static members initialization macros
// call before using the template, once per template instance
#define INIT_UNIQUE_CAT(x, y) unique_value<x, y>::value_type unique_value<x,y>::m_counter=0
#define INIT_UNIQUE(x) INIT_UNIQUE_CAT(x, default_unique_category)

#endif