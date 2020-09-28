template <typename FirstType, typename SecondType>
class Pair {
public:
	Pair(FirstType f, SecondType s);

	FirstType getFirst();
	SecondType getSecond();

private:
	FirstType first;
	SecondType second;
};

template <typename FirstType, typename SecondType>
Pair<FirstType, SecondType>::Pair(FirstType f, SecondType s)
		: first(f), second(s) {
}

template <typename FirstType, typename SecondType>
FirstType Pair<FirstType, SecondType>::getFirst() {
	return first;
}

template <typename FirstType, typename SecondType>
SecondType Pair<FirstType, SecondType>::getSecond() {
	return second;	
}
