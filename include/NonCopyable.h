/*********************************************
 *
 *
 *
 * \brief 使所有的子类禁用拷贝构造函数和赋值符号
 *
 *
 *
 *
 *
 * *******************************************/

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class Noncopyable
{

	protected:

		/**
		 *\brief 缺省构造函数
		 *						 
		 */
		Noncopyable() {};
		/**
		 *\brief 缺省析构函数
		 *
		 */
		~Noncopyable() {};

	private:

		/**
		 *\brief 拷贝构造函数
		 *
		 */
		Noncopyable(const Noncopyable&);
		/**
		 *\brief 赋值操作符号
		 *
		 */
		const Noncopyable & operator= (const Noncopyable &);

};

#endif
