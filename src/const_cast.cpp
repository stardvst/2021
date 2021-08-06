class S
{
public:
	int &get_i()
	{
		return const_cast<int &>(static_cast<const S *>(this)->get_i());
	}

	const int &get_i() const
	{
		return i;
	}

private:
	int i;
};

class SBetter
{
public:
	// decltype(auto) returns exact deduced type

	decltype(auto) get_i()
	{
		return get_i_common(this);
	}

	decltype(auto) get_i() const
	{
		return get_i_common(this);
	}

private:
	template <typename Self>
	static decltype(auto) get_i_common(Self *self)
	{
		return (self->i);
	}

	int i;
};

int main()
{
	S s;
	s.get_i() = 42;

	SBetter sb;
	sb.get_i() = 42;
}
