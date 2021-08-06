class int_pointer_holder
{
public:
	int_pointer_holder(int *ptr) : data(ptr), was_const(false) {}
	int_pointer_holder(const int *ptr) : data(ptr), was_const(true) {}

	int *get_mutable_data()
	{
		if (was_const)
		{
			//throw runtime_error("You cannot modify it!");
			return nullptr;
		}
		else
			return const_cast<int *>(data);
	}

	const int *get_data() const
	{
		return data;
	}

private:
	const int *data = nullptr;
	bool was_const = false;
};

class int_pointer_holder_better
{
public:
	int_pointer_holder_better(int *ptr) : data(ptr), mut_data(ptr) {}
	int_pointer_holder_better(const int *ptr) : data(ptr), mut_data(nullptr) {}

	int *get_mutable_data()
	{
		return mut_data;
	}

	const int *get_data() const
	{
		return data;
	}

private:
	const int *data = nullptr;
	int *mut_data = nullptr;
};

int main()
{
	int i = 42;
	int_pointer_holder iph{ &i };
	*iph.get_mutable_data() = 15;

	const int ci = 42;
	int_pointer_holder ciph{ &ci };
	//*ciph.get_mutable_data() = 15;

	int i1 = 42;
	int_pointer_holder_better iph1{ &i1 };
	*iph1.get_mutable_data() = 15;

	const int ci1 = 42;
	int_pointer_holder_better ciph1{ &ci1 };
	//*ciph1.get_mutable_data() = 15;
}
