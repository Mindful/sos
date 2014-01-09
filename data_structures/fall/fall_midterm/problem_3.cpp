//queue combination method
//q1 = lhs, q2 = rhs

//if the queues are uneven, the resultant queue is ordered evenly up until the point where the shorter queue ran out
//so like [1,3,5,7,9] and [2,4,6] would give [1,2,3,4,5,6,7,9]
template <typename Object>
queue merge(queue<Object>& lhs, queue<Object>& rhs){
	queue<Object> result;
	while(!lhs.isEmpty() || !rhs.isEmpty()){
		if(!lhs.isEmpty()){
			result.enqueue(lhs.dequeue());
		}
		if(!rhs.isEmpty()){
			result.enqueue(rhs.dequeue());
		}
	}

}