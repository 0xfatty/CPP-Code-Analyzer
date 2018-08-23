//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linkedlist.h"
#include "queue.h"
#include "stack.h"

TEST_CASE("LinkedList class", "[LinkedList]"){

	LinkedList<int> ll0(4);

    SECTION("Default constructor"){
		LinkedList<int> ll1;

		REQUIRE(ll1.size() == 0);
    }

    SECTION("Constructor with head"){
		LinkedList<int> ll1(5);

		REQUIRE(ll1.size() == 1);
    }

    SECTION("Copy constructor"){
		LinkedList<int> ll1(ll0);

		REQUIRE(ll1.size() == 1);
		REQUIRE(ll1.get(0) == 4);
    }

    SECTION("add"){
		ll0.add(722);

		REQUIRE(ll0.size() == 2);
		REQUIRE(ll0.get(1) == 722);
    }

    SECTION("addToFront"){

		ll0.addToFront(238);

		REQUIRE(ll0.size() == 2);
		REQUIRE(ll0.get(0) == 238);
    }

    SECTION("get"){
		REQUIRE(ll0.get(0) == 4);
    }

    SECTION("size"){
		ll0.add(797);
		ll0.addToFront(9);
		ll0.add(55);

		REQUIRE(ll0.size() == 4);
    }

    SECTION("remove"){
		ll0.add(5);
		ll0.add(6);
		ll0.add(7);
		ll0.add(8);
		ll0.add(9);
		ll0.add(10);

		ll0.remove(0);

		REQUIRE(ll0.size() == 6);
		REQUIRE(ll0.get(0) == 5);

		ll0.remove(ll0.size()-1);

		REQUIRE(ll0.size() == 5);
		REQUIRE(ll0.get(ll0.size()-1) == 9);

		ll0.remove(2);

		REQUIRE(ll0.size() == 4);
		REQUIRE(ll0.get(2) == 8);
    }

    SECTION("[] operator"){

		REQUIRE(ll0[0] == 4);

		ll0[0] = 9;

		REQUIRE(ll0[0] == 9);
    }

    SECTION("assignment operator"){
		LinkedList<int> ll2;
		ll2 = ll0;

		REQUIRE(ll2.size() == 1);
		REQUIRE(ll2.get(0) == 4);
    }
}


TEST_CASE("Stack class", "[stack]"){

	Stack<int> stk0;
	stk0.push(87);
	stk0.push(62);
	stk0.push(5);

    SECTION("Push"){

		stk0.push(25);

		REQUIRE(stk0.peek() == 25);
    }

    SECTION("Pop"){

		REQUIRE(stk0.pop() == 5);
		REQUIRE(stk0.peek() == 62);
    }

    SECTION("Peek"){

		REQUIRE(stk0.peek() == 5);
		REQUIRE(stk0.peek() == 5);
    }
}


TEST_CASE("Queue class", "[queue]"){

	Queue<int> q0;
	q0.enqueue(1);
	q0.enqueue(2);
	q0.enqueue(3);

    SECTION("Enqueue"){
		Queue<int> q1;

		REQUIRE(q1.isEmpty() == true);

		q1.enqueue(10);

		REQUIRE(q1.isEmpty() == false);
    }

    SECTION("Dequeue"){

		REQUIRE(q0.dequeue() == 1);
		REQUIRE(q0.dequeue() == 2);
    }

    SECTION("Peek"){

		REQUIRE(q0.peek() == 1);
		REQUIRE(q0.peek() == 1);

    }
}

