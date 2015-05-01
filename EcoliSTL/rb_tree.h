#ifndef _ECSTL_RB_TREE_H
#define _ECSTL_RB_TREE_H
#include "iterator.h"
#include "allocator.h"


namespace EcSTL{

	typedef bool _rb_tree_node_color;
	const _rb_tree_node_color _rb_tree_black = 1;
	const _rb_tree_node_color _rb_tree_red = 0;
	class _rb_tree_node_base{
	public:
		typedef _rb_tree_node_base* base_ptr;
		typedef _rb_tree_node_color color_type;
		base_ptr parent;
		base_ptr left;
		base_ptr right;
		color_type color;
		_rb_tree_node_base() :parent(nullptr), left(nullptr), right(nullptr), color(_rb_tree_red){}

		static base_ptr min_rb_tree_node(base_ptr _x){
			if (_x){
				while (_x->left) {
					_x = _x->left;
				}
				return _x;
			}
			else{
				return nullptr;
			}
		}

		static base_ptr max_rb_tree_node(base_ptr _x){
			if (_x){
				while (_x->right) {
					_x = _x->right;
				}
				return _x;
			}
			else{
				return nullptr;
			}
		}
	};

	template<class Value>
	class _rb_tree_node :public _rb_tree_node_base{
	public:
		typedef Value value_type;
		Value data;
		_rb_tree_node(const value_type& val) :data(val){}
	};

	class _rb_tree_base_iterator{
	public:
		typedef _rb_tree_node_base* base_ptr;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		base_ptr node;

		_rb_tree_base_iterator(base_ptr _x) :node(_x){}	//constructor;
		_rb_tree_base_iterator() :node(nullptr){}

		void increment(){

			if (node->right){
				node = node->right;
				while (node->left) {
					node = node->left;
				}
			}
			else{
				base_ptr p = node->parent;

				while (node == p->right) {
					node = p;
					p = p->parent;
				}

				if (node->right != p){
					node = p;
				}
			}
		}

		void decrement(){
			if (node->color == _rb_tree_red && node->parent->parent == node){ //node Ϊ headerʱ
				node = node->right;
			}
			else if (node->left){
				base_ptr cur = node->left;
				while (cur->right) {
					cur = cur->right;
				}
				node = cur;
			}
			else{
				base_ptr cur = node->parent;
				while (node == cur->left){
					node = cur;
					cur = cur->parent;
				}
				node = cur;
			}
		}
	};

	template<class Value, class Ref, class Ptr>
	class _rb_tree_iterator : public _rb_tree_base_iterator{
	public:
		typedef Value value_type;
		typedef Ref reference;
		typedef Ptr pointer;

		typedef _rb_tree_iterator<Value, Ref, Ptr> iterator;
		typedef _rb_tree_node<Value>* _link_type;

		_rb_tree_iterator(_link_type p) :_rb_tree_base_iterator((base_ptr)p){}
		_rb_tree_iterator(){}
		_rb_tree_iterator(const iterator& it) :_rb_tree_base_iterator(it.node){}

		reference operator*()const{
			return ((_link_type)node)->data;
		}

		pointer operator->()const{
			return &(operator*());
		}

		iterator& operator++(){
			increment();
			return *this;
		}

		iterator operator++(int){
			iterator tmp = *this;
			increment();
			return tmp;
		}

		iterator& operator--(){
			decrement();
			return *this;
		}

		iterator operator--(int){
			iterator tmp = *this;
			decrement();
			return *this;
		}

		bool operator==(const iterator& rhs)const{
			return this->node == rhs.node;
		}

		bool operator!=(const iterator& rhs)const{
			return this->node != rhs.node;
		}

	};

	template<class Value, class Key, class ExtractKey, class Cmp, class Alloc = allocator<_rb_tree_node<Value>>>
	class rb_tree{
	public:
		typedef _rb_tree_iterator<Value, Value&, Value*> iterator;
		typedef rb_tree<Value, Key, ExtractKey, Cmp, Alloc> self;
		typedef Key key_type;
		typedef Value value_type;
		typedef _rb_tree_node_base* base_ptr;
		typedef _rb_tree_node<value_type>* _link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _rb_tree_node_base::color_type color_type;
		typedef value_type& reference;

	protected:

		//数据成员
		_link_type header;
		size_type node_count;
		Cmp cmpfunc;

	private:
		void init(){
			header = getnode();
			header->right = header;
			header->left = header;
			header->parent = nullptr;
			header->color = _rb_tree_red;
		}

	protected:
		_link_type getnode(){ return (_link_type)Alloc::allocate(1); }

		void put_node(_link_type _x){ Alloc::deallocator(_x); }

		_link_type create_node(const value_type& val){
			_link_type tmp = getnode();
			construct(&(tmp->data), val);
			return tmp;
		}

		void destroy_node(_link_type _x){
			destroy(&_x->data);
			put_node(_x);
		}

		void _m_erase(_link_type _x){
			while (_x) {
				_m_erase(_x->left);
				_link_type _y = _x->right;
				destroy_node(_x);
				_x = _y;
			}
		}

		_link_type& leftmost()const{ return (_link_type&)header->left; }
		_link_type& rightmost()const{ return (_link_type&)header->right; }
		_link_type& root_of_tree()const{ return (_link_type&)header->parent; }


		static _link_type max_node(){ return (_link_type)_rb_tree_node_base::max_rb_tree_node(); }
		static _link_type min_node(){ return (_link_type)_rb_tree_node_base::min_rb_tree_node(); }

		static _link_type& get_left(_link_type _x){ return (_link_type&)_x->left; }
		static _link_type& get_right(_link_type _x){ return (_link_type&)_x->right; }
		static _link_type& get_parent(_link_type _x){ return (_link_type&)_x->parent; }
		static const Key& get_key(_link_type _x){ return ExtractKey()(_x->data); }
		static reference get_value(_link_type _x){ return _x->data; }
		static color_type& get_color(_link_type _x){ return (color_type&)_x->color; }


	public:
		rb_tree(const Cmp& _cmp = Cmp()) :node_count(0), cmpfunc(_cmp){ init(); }


		self& operator=(const self& others);

		void clear(){
			if (node_count){
				_m_erase(header->parent);
				leftmost() = header;
				rightmost() = header;
				root_of_tree() = nullptr;
				node_count = 0;
			}
		}

		iterator begin(){ return leftmost(); }
		iterator end(){ return header; }
		bool empty()const{ return node_count == 0; }
		size_type size()const{ return node_count; }
		size_type max_size()const{ return size_type(-1); }


		pair<iterator, bool> insert_unique(const value_type& val);
		iterator insert_equal(const value_type& val);

		iterator _insert(base_ptr _x, base_ptr _y, const value_type& val);



		void print_prev()const{
			print((_link_type)header->parent);
		}

		void print(base_ptr cur)const{
			if(cur){
				print(cur->left);
				cout << ((_link_type)cur)->data << " ";
				print(cur->right);
			}
		}


	};


	void left_rotate_rb_tree(_rb_tree_node_base* x, _rb_tree_node_base*& root){
		typedef _rb_tree_node_base* base_ptr;
		base_ptr y = x->right;
		x->right = y->left;

		if (y->left){
			y->left->parent = x;
		}
		y->parent = x->parent;

		if (x == root){
			root = y;
		}
		else if (x == x->parent->left){
			x->parent->left = y;
		}
		else{
			x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	}

	void right_rotate_rb_tree(_rb_tree_node_base* x, _rb_tree_node_base*& root){
		typedef _rb_tree_node_base* base_ptr;
		base_ptr y = x->left;

		x->left = y->right;

		if (y->right){
			y->right->parent = x;
		}

		y->parent = x->parent;

		if (x == root){
			root = y;
		}
		else if (x == x->parent->right){
			y->parent->right = y;
		}
		else{
			y->parent->left = y;
		}
		y->right = x;
		x->parent = y;

	}


	//找到插入的位置
	//insert_unique使用于不可重复的rb_tree;
	/*
		template<class Value, class Key, class ExtractKey, class Cmp, class Alloc>
		pair<typename rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::iterator, bool> rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::insert_unique(const value_type& val){
		_linke_type& root = root_of_tree();

		if (!root){
		root = create_node(val);

		}

		}*/

	template<class Value, class Key, class ExtractKey, class Cmp, class Alloc>
	typename rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::iterator rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::insert_equal(const value_type& val){
		_link_type _x = header;
		_link_type _y = root_of_tree();
		ExtractKey key_getter = ExtractKey();
		while (_y){
			_x = _y;
			if (cmpfunc(key_getter(val), get_key(_y))){
				_y = get_left(_y);
			}
			else{
				_y = get_right(_y);
			}
		}
		return _insert(_y, _x, val);
	}

	template<class Value, class Key, class ExtractKey, class Cmp, class Alloc>
	typename rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::iterator rb_tree<Value, Key, ExtractKey, Cmp, Alloc>::_insert(base_ptr _x, base_ptr _y, const value_type& val){
		_link_type x = (_link_type)_x;
		_link_type y = (_link_type)_y;
		_link_type z = create_node(val);


		if (y == header || x != nullptr || cmpfunc(ExtractKey()(val), get_key(y))){
			get_left(y) = z;
			if (header == y){
				root_of_tree() = z;
				rightmost() = z;
			}
			else if (y == leftmost()){
				leftmost() = y;
			}
		}
		else
		{
			get_right(y) = z;
			if (y == rightmost()){
				rightmost() = z;
			}
		}

		get_parent(z) = y;
		get_left(z) = nullptr;
		get_right(z) = nullptr;

		_rb_tree_insert_balance(z, header->parent);

		++node_count;

		return iterator(z);
	}




	void _rb_tree_insert_balance(_rb_tree_node_base* x, _rb_tree_node_base*& root){
		x->color = _rb_tree_red;
		while (x != root && x->parent->color == _rb_tree_red) {
			if (x->parent == x->parent->parent->left){ //如果插入节点的父节点为祖父节点的左节点
				_rb_tree_node_base* y = x->parent->parent->right; //根据父节点的兄弟节点的性质进行区分；

				if (y && y->color == _rb_tree_red){ //如果父节点的兄弟节点为红色，则进行重新着色，以祖父节点为新的节点进行循环 case 1
					x->parent->color = _rb_tree_black;
					x->parent->parent = _rb_tree_red;
					y->color = _rb_tree_black;
					x = x->parent->parent;
				}
				else{								//无伯父节点，或者伯父节点颜色为黑

					if (x == x->parent->right){		//如果节点x为父节点的右孩子 case 2;
						x = x->parent;
						left_rotate_rb_tree(x, root);
					}

					x->parent->color = _rb_tree_black;
					x->parent->parent->color = _rb_tree_red;
					right_rotate_rb_tree(x->parent->parent, root);

				}
			}
			else
			{
				_rb_tree_node_base* y = x->parent->parent->left;

				if (y && y->color == _rb_tree_red){
					x->parent->color = _rb_tree_black;
					x->parent->parent->color = _rb_tree_red;
					y->color = _rb_tree_black;
					x = x->parent->parent;
				}
				else{

					if (x == x->parent->left){
						x = x->parent;
						right_rotate_rb_tree(x, root);
					}
					x->parent->color = _rb_tree_black;
					x->parent->parent->color = _rb_tree_red;
					left_rotate_rb_tree(x->parent->parent, root);

				}
			}

			root->color = _rb_tree_black;
		}

		root->color = _rb_tree_black;
	}



}

#endif