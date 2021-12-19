/*
	cout capture based tests will fail
	when verbose debug is enabled
*/
//#define DEBUG

#include <iostream>
#include <gtest/gtest.h>
#include "sequence.hpp"

class SequenceTests : public ::testing::Test {
public:
	Sequence<int, int>* t0;
	Sequence<int, int>* t1;
	Sequence<int, int>* t2;
	Sequence<int, int>::iterator* itr_v;
	Sequence<int, int>::iterator* itr_e;
	void SetUp() {
		t0 = new Sequence<int, int>;
		t1 = new Sequence<int, int>(8, 8);
		t1 -> push_back(1,7);
		t1 -> push_back(3,1);
		t1 -> push_back(4,8);
		t1 -> push_back(9,0);
		t2 = new Sequence<int, int>(*t1);
		t2 -> swap(9, 1);
		t2 -> push_front(2, 5);
		itr_v = new Sequence<int, int>::iterator(*t1);
		itr_e = new Sequence<int, int>::iterator(*t2);
	}
	void TearDown(){
		delete t0;
		delete t1;
		delete t2;
		delete itr_v;
		delete itr_e;
	}
};

TEST_F(SequenceTests, DefaultConstructor) {
	Sequence<int, int> tc;
	Sequence<int, int>::iterator itr(tc);
	EXPECT_EQ( 0, tc.size() );
	EXPECT_EQ( true, itr.end() );
}

TEST_F(SequenceTests, InitConstructor) {
	Sequence<int, int> tc(1, 2);
	Sequence<int, int>::iterator itr(tc);
	EXPECT_EQ( 1, tc.size() );
	EXPECT_EQ( 1, itr.key() );
	EXPECT_EQ( 2, itr.info() );
}

TEST_F(SequenceTests, CopyConstructor) {
	Sequence<int, int> tc(*t1);
	EXPECT_EQ( 5, tc.size() );
}

TEST_F(SequenceTests, EqualityOperator) {
	Sequence<int, int> tc(*t1);
	EXPECT_EQ( true, (tc == *t1));
	EXPECT_EQ( false, (tc == *t0));
}

TEST_F(SequenceTests, InequalityOperator) {
	Sequence<int, int> tc(*t1);
	EXPECT_EQ( false, (tc != *t1));
	EXPECT_EQ( true, (tc != *t0));
}

TEST_F(SequenceTests, AssignmentOperator) {
	Sequence<int, int> tc;
	tc = *t1;
	EXPECT_EQ( true, (tc == *t1));
}

TEST_F(SequenceTests, AdditionOperator) {
	Sequence<int, int> tc(1,0);
	Sequence<int, int> td(2,1);
	Sequence<int, int> te;
	te = tc + td;
	Sequence<int, int> tf(1,0);
	tf.push_back(2, 1);
	EXPECT_EQ( true, (te == tf));
}

TEST_F(SequenceTests, AdditionAssignmentOperator) {
	Sequence<int, int> tc(1,0);
	Sequence<int, int> td(2,1);
	tc += td;
	Sequence<int, int> tf(1,0);
	tf.push_back(2, 1);
	EXPECT_EQ( true, (tc == tf));
}

TEST_F(SequenceTests, InsertionOperator) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.push_back(2, 0);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[1] 0\n[2] 0\n");
}

TEST_F(SequenceTests, PushFront) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.push_front(2, 0);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[2] 0\n[1] 0\n");
}

TEST_F(SequenceTests, PushBack) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.push_back(2, 0);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[1] 0\n[2] 0\n");
}

TEST_F(SequenceTests, InsertBefore) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.push_back(1,5);
	tc.insert_before(9, 9, 1);
	tc.insert_before(7, 7, 1, 2);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[9] 9\n[1] 0\n[7] 7\n[1] 5\n");
}

TEST_F(SequenceTests, InsertAfter) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.insert_after(9, 9, 1);
	tc.insert_after(7, 7, 9);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[1] 0\n[9] 9\n[7] 7\n");
}

TEST_F(SequenceTests, Replace) {
	testing::internal::CaptureStdout();
	Sequence<int, int> tc(1,0);
	tc.replace(5, 5, 1);
	std::cout << tc;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[5] 5\n");
}

TEST_F(SequenceTests, Purge) {
	Sequence<int, int> tc(1,0);
	Sequence<int, int> td;
	EXPECT_EQ( true, tc.purge() );
	EXPECT_EQ( 0, tc.size() );
	EXPECT_EQ( false, td.purge() );
}

TEST_F(SequenceTests, PopFront) {
	Sequence<int, int> tc(1,5);
	Sequence<int, int> td;
	tc.push_back(2,1);
	EXPECT_EQ( 5, tc.pop_front() );
	EXPECT_EQ( 0, td.pop_front() );
	EXPECT_EQ( 1, tc.size() );
}

TEST_F(SequenceTests, PopBack) {
	Sequence<int, int> tc(1,5);
	Sequence<int, int> td;
	tc.push_back(2,1);
	EXPECT_EQ( 1, tc.pop_back() );
	EXPECT_EQ( 0, td.pop_back() );
	EXPECT_EQ( 1, tc.size() );
}

TEST_F(SequenceTests, RemoveAfter) {
	t1 -> remove_after(4);
	EXPECT_EQ( 4, t1 -> size() );
	t1 -> remove_after(8);
	EXPECT_EQ( 3, t1 -> size() );
}

TEST_F(SequenceTests, RemoveBefore) {
	t1 -> remove_before(4);
	EXPECT_EQ( 4, t1 -> size() );
	t1 -> remove_before(1);
	EXPECT_EQ( 3, t1 -> size() );
}

TEST_F(SequenceTests, Remove) {
	t1 -> remove(4);
	EXPECT_EQ( 4, t1 -> size() );
	t1 -> remove(1);
	EXPECT_EQ( 3, t1 -> size() );
}

TEST_F(SequenceTests, Empty) {
	EXPECT_EQ( true, t0 -> empty() );
	EXPECT_EQ( false, t1 -> empty() );
}

TEST_F(SequenceTests, Size) {
	EXPECT_EQ( true, t0 -> empty() );
	EXPECT_EQ( false, t1 -> empty() );
}

TEST_F(SequenceTests, Print) {
	testing::internal::CaptureStdout();
	t1 -> print();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "Key 8: 8\nKey 1: 7\nKey 3: 1\nKey 4: 8\nKey 9: 0\n" );
}

TEST_F(SequenceTests, GetInfo) {
	EXPECT_EQ( 0, t0 -> get_info(1, 2) );
	EXPECT_EQ( 8, t1 -> get_info(4) );
}


TEST_F(SequenceTests, Begin) {
	Sequence<int, int>::iterator itr = t1 -> begin();
	EXPECT_EQ( 8, itr.key() );
	EXPECT_EQ( 8, itr.info() );
}

TEST_F(SequenceTests, End) {
	while(*itr_v != t1 -> end()) {
		(*itr_v)++;
	}
	EXPECT_EQ( *itr_v, t1 -> end() );
}

TEST_F(SequenceTests, ClearInfo) {
	t1 -> clear_info(0);
	testing::internal::CaptureStdout();
	std::cout << *t1;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[8] 0\n[1] 0\n[3] 0\n[4] 0\n[9] 0\n");
}

TEST_F(SequenceTests, Swap) {
	t1 -> swap(3, 4);
	testing::internal::CaptureStdout();
	std::cout << *t1;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[8] 8\n[1] 7\n[4] 8\n[3] 1\n[9] 0\n");
}

TEST_F(SequenceTests, IteratorInitConstructor) {
	Sequence<int, int>::iterator itr_t(*t1);
	EXPECT_EQ( 8, *itr_t );
}

TEST_F(SequenceTests, IteratorCopyConstructor) {
	EXPECT_EQ( false, itr_v -> end() );
}

TEST_F(SequenceTests, IteratorAssignment) {
	EXPECT_NE( *itr_e, *itr_v );
	*itr_e = *itr_v;
	EXPECT_EQ( *itr_e, *itr_v );
}

TEST_F(SequenceTests, IteratorPostIncrement) {
	Sequence<int, int>::iterator itr_t(*t1);
	EXPECT_EQ( 8, (itr_t++).key() );
	EXPECT_EQ( 1, itr_t.key() );
}

TEST_F(SequenceTests, IteratorPreIncrement) {
	Sequence<int, int>::iterator itr_t(*t1);
	EXPECT_EQ( 1, (++itr_t).key() );
}

TEST_F(SequenceTests, IteratorDereference) {
	EXPECT_EQ( 8, **itr_v );
}

TEST_F(SequenceTests, IteratorEquality) {
	
	EXPECT_EQ( true, *itr_v == *itr_v );
	EXPECT_EQ( false, *itr_v == *itr_e );
}

TEST_F(SequenceTests, IteratorNonEquality) {

	EXPECT_EQ( true, *itr_v != *itr_e );
}

TEST_F(SequenceTests, IteratorGetKey) {
	(*itr_v)++;
	EXPECT_EQ( 1, itr_v -> key() );
}

TEST_F(SequenceTests, IteratorGetInfo) {
	(*itr_v)++;
	EXPECT_EQ( 7, itr_v -> info() );
}

TEST_F(SequenceTests, IteratorEnd) {
	(*itr_e) = t1 -> end();
	EXPECT_EQ( false, itr_v -> end() );
	EXPECT_EQ( true, itr_e -> end() );
}

int add2(const int& var1, const int& var2) {
	return var1 + var2;
}

TEST_F(SequenceTests, JoinDuplicates) {
	//same list twice
	Sequence<int, int> seq_t(*t1);
	testing::internal::CaptureStdout();
	std::cout<< join<int, int>(seq_t, *t1, &add2);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output, "[8] 16\n[1] 14\n[3] 2\n[4] 16\n[9] 0\n");
	//different lists
	t1 -> replace(5, 6, 9);
	t1 -> replace(9, 2, 1);
	testing::internal::CaptureStdout();
	std::cout<< join<int, int>(seq_t, *t1, &add2);
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output2, "[8] 16\n[9] 2\n[3] 1\n[4] 8\n[5] 6\n[1] 7\n[3] 1\n[4] 8\n[9] 0\n");
	//different list sizes
	testing::internal::CaptureStdout();
	std::cout<< join<int, int>(*t1, *t2, &add2);
	std::string output3 = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output3, "");
	//one empty list
	testing::internal::CaptureStdout();
	std::cout<< join<int, int>(*t1, *t0, &add2);
	std::string output4 = testing::internal::GetCapturedStdout();
	EXPECT_EQ( output4, "");
}

int main (int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
