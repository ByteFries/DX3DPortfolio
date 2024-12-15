#pragma once
class AABB
{
public:
	AABB()
	{}

	float xEnd[2] = {0,0};
	float yEnd[2] = {0,0};
	float zEnd[2] = {0,0};
};

struct EndPoint
{
	enum Type { BEGIN = 0, END = 1};
	Type type;
	float value;
	int index;

	bool operator<(const EndPoint& other) const
	{
		if (value != other.value) {
			return value < other.value;
		}
		return type < other.type;
	}

	bool operator==(const EndPoint& other) const
	{
		return (type == other.type) && (value == other.value);
	}
};

struct OverlapPair
{
	OverlapPair(int i0, int i1)
	{
		if (i0 < i1)
		{
			index0 = i0;
			index1 = i1;
		}
		else
		{
			index0 = i1;
			index1 = i0;
		}
	}

	bool operator==(const OverlapPair& other) const
	{
		return index0 == other.index0 && index1 == other.index1;
	}

	bool operator<(const OverlapPair& other) const {
		if (index0 != other.index0) return index0 < other.index0;
		return index1 < other.index1;
	}

	OverlapPair(const OverlapPair& other) = default;

	struct Hash
	{
		std::size_t operator()(const OverlapPair& p) const
		{
			std::size_t h1 = std::hash<unsigned int>()(p.index0);
			std::size_t h2 = std::hash<unsigned int>()(p.index1);
			return h1 ^ (h2 << 1);
		}
	};
	int index0, index1;
};