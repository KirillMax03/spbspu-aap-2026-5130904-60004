#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace maksimov
{
  struct SumDupCount
  {
    SumDupCount();
    void operator()(int num);
    std::size_t operator()() const;

  private:
    const std::size_t min_length_;
    long long pre1_;
    long long pre2_;
    std::size_t count_;
    std::size_t matches_;
  };
}

maksimov::SumDupCount::SumDupCount():
  min_length_(3),
  pre1_(0),
  pre2_(0),
  count_(0),
  matches_(0)
{}

void maksimov::SumDupCount::operator()(int num)
{
  ++count_;
  if (count_ >= min_length_ && num == pre1_ + pre2_)
  {
    ++matches_;
  }
  pre2_ = pre1_;
  pre1_ = num;
}

std::size_t maksimov::SumDupCount::operator()() const
{
  if (count_ < min_length_)
  {
    throw std::length_error("Error: sequence too short");
  }
  return matches_;
}

int main()
{
  try
  {
    maksimov::SumDupCount counter;
    int value = 0;
    while (true)
    {
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Error: invalid input format");
      }
      if (value == 0)
      {
        break;
      }
      counter(value);
    }
    std::cout << counter() << "\n";
    return 0;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::length_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
