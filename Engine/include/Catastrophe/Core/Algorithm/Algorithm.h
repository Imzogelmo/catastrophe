//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Algorithm/Copy.h"
#include "Catastrophe/Core/Algorithm/Search.h"
#include "Catastrophe/Core/Algorithm/BinarySearch.h"
#include "Catastrophe/Core/Algorithm/Merge.h"
#include "Catastrophe/Core/Algorithm/Heap.h"
#include "Catastrophe/Core/Algorithm/Partition.h"


CE_NAMESPACE_BEGIN


// Algorithm.h
//
// Implements the standard algorithm library. Note that there are also a few non-standard
// functions defined as well, as these are deemed a useful addition to an algorithm library,
// or may simply be supplied as a generic or reusable function in favor of a hidden one in cases
// where it may be used internally by some other source.
//
// Note that these functions have been split up into separate header files in order to keep
// compilation time as fast as possible. These files are categorized in an obvious and
// intuitive manner as possible:
//
//    "algobase.h"			(most commonly used and low level functions are mitigated here.)
//    "minmax.h"			(algorithms dealing with minimum and maximum values.)
//    "Copy.h"				(algorithms that Copy, set, or modify data.)
//    "search.h"			(algorithms that perform various range-based searches on random data.)
//    "binary_search.h"		(algorithms that perform searches on sorted data.)
//    "merge.h"				(algorithms that perform set operations on sorted ranges.)
//    "heap.h"				(algorithms that create, maintain, or perform sorting on binary heaps.)
//    "partition.h"			(algorithms that deal with partitioning.)
//    "sort.h"				(sorting algorithms.)
//
//
// List of available algorithms:

//    adjacent_find
//    all_of
//    any_of
//    binary_find
//    binary_search
//    binary_sort
//    clamp
//    clamp_range
//    Copy
//    CopyBackward
//    copy_if
//    copy_n
//    count
//    count_if
//    equal
//    equal_range
//    Fill
//    FillValues
//    Find
//    find_end
//    find_first_of
//    find_first_not_of
//    FindLastOf
//    find_last_not_of
//    FindIf
//    find_if_not
//    for_each
//    generate
//    generate_n
//    heap_sort
//    includes
//    inplace_merge
//    is_heap
//    is_heap_until
//    is_partitioned
//    is_sorted
//    is_sorted_until
//    iter_swap
//    lexicographical_compare
//    lower_bound
//    MakeHeap
//    max
//    max_element
//    merge
//    merge_sort
//    min
//    min_element
//    minmax
//    minmax_element
//    mismatch
//    next_permutation			(not implemented)
//    none_of
//    nth_element				(not implemented)
//    partial_sort
//    partial_sort_copy			(not implemented)
//    partition
//    partition_copy
//    partition_point
//    pop_heap
//    prev_permutation			(not implemented)
//    push_heap
//    random_shuffle
//    remove
//    remove_copy
//    remove_copy_if
//    remove_if
//    replace
//    replace_copy
//    replace_copy_if
//    replace_if
//    reverse
//    reverse_copy
//    rotate
//    rotate_copy
//    search
//    search_n
//    set_difference
//    set_intersection
//    set_symmetric_difference
//    set_union
//    shuffle					(not implemented)
//    sort
//    SortHeap
//    stable_partition
//    stable_partition_copy
//    stable_sort
//    Swap
//    swap_ranges
//    transform
//    unique
//    unique_copy
//    upper_bound



CE_NAMESPACE_END




