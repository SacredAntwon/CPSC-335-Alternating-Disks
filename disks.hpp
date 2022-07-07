#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// TODO
#include <functional>
#include <iostream>

enum disk_color { DISK_LIGHT, DISK_DARK };

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

      assert(light_count > 0);

      for (size_t i = 0; i < _colors.size(); i += 2) {
        _colors[i] = DISK_DARK;
      }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

    // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is dark, the second disk at index 1
  // is light, and so on for the entire row of disks.
  bool is_initialized() const {
    // This will loop through all disks
    for (size_t i = 0; i < total_count(); i++) {
      // If it is an even index (including 0), it should be a dark disk
      // or a value of 1. If it is not a 1, we return false.
      if (i % 2 == 0) {
        if (get(i) != 1) {
          return false;
        }
      }

      // If it is an odd index, it should be a light disk
      // or a value of 0. If it is not a 0, we return false.
      else {
        if (get(i) != 0) {
          return false;
        }
      }
    }

    // Will return true if it makes it through the for loop
    return true;
  }

  // Return true when this disk_state is fully sorted, with all dark disks on
  // the left (low indices) and all dark disks on the right (high indices).
  bool is_sorted() const {
    // Checks to see if first half is all light disks.
    // If left side is sorted and all light, this means that the right side
    // is also sorted but dark, so no need to check right side.
    for (size_t i = 0; i < light_count(); i++) {
      // 0 is a light disk. Return false if it is not 0.
      if (get(i) != 0) {
        return false;
      }
    }

    // Will return true if it makes it through the for loop
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  auto sorted_lawn(before);

  int swap_num = 0;
  int repeat_num = (sorted_lawn.light_count() + 1) / 2;
  // This for loop will run the number of times it does a full round trip.
  for(int i = 0; i < repeat_num; i++) {
    // This for loop is to go from left to right (lTr)
    for (size_t lTr = 0; lTr < sorted_lawn.total_count() - 1; lTr++) {
      // If left index is greater then right index, we swap meaning
      // we move the dark disk to the right and light disk to the left.
      // We then increase the swap count by 1 since a swap occured.
      if(sorted_lawn.get(lTr) > sorted_lawn.get(lTr + 1)) {
        sorted_lawn.swap(lTr);
        swap_num += 1;
      }
    }

    // This for loop is to go from right to left (rTl)
    for (size_t rTl = sorted_lawn.total_count() - 1; rTl > 0; rTl--) {
      // If left index (rTl-1) is greater then right index, we swap meaning
      // we move the dark disk to the right and light disk to the left.
      // We then increase the swap count by 1 since a swap occured.
      if(sorted_lawn.get(rTl) < sorted_lawn.get(rTl - 1)) {
        sorted_lawn.swap(rTl - 1);
        swap_num += 1;
      }
    }
  }

  return sorted_disks(sorted_lawn, swap_num);
}


// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
  auto sorted_alter(before);

  int swap_num = 0;
  int repeat_num = sorted_alter.light_count() + 1;

  // This for loop will loop the number of runs
  for(int i = 0; i < repeat_num; i++) {
    // This if will check to do runs 1, 3, 5, etc. meaning it will start
    // with the leftmost disk.
    if (i % 2 == 0) {
      for (size_t ind = 0; ind < sorted_alter.total_count() - 1; ind++) {
        // If left index is greater then right index, we swap meaning
        // we move the dark disk to the right and light disk to the left.
        // We then increase the swap count by 1 since a swap occured.
        if(sorted_alter.get(ind) > sorted_alter.get(ind + 1)) {
          sorted_alter.swap(ind);
          swap_num += 1;
        }
      }
    }

    // This else will do runs 2, 4, 6, etc. meaning it will start
    // with the second leftmost disk.
    else {
      for (size_t ind = 1; ind < sorted_alter.total_count() - 2; ind++) {
        // If left index is greater then right index, we swap meaning
        // we move the dark disk to the right and light disk to the left.
        // We then increase the swap count by 1 since a swap occured.
        if(sorted_alter.get(ind) > sorted_alter.get(ind + 1)) {
          sorted_alter.swap(ind);
          swap_num += 1;
        }
      }
    }
  }


  return sorted_disks(sorted_alter, swap_num);
}
