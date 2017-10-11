namespace std
{
  template <intmax_t A, intmax_t Denom>
  struct ratio
  {
    
  };

  typedef ratio<1, 1000000000000000000LL> atto;
  typedef ratio<1, 1000000000000000LL> femto;
  typedef ratio<1, 1000000000000LL> pico;

  typedef ratio<1, 1000000000> nano;
  typedef ratio<1, 1000000> micro;
  typedef ratio<1, 1000> milli;
  typedef ratio<1, 100> centi;
  typedef ratio<1, 10> deci;
  typedef ratio<10, 1> deca;
  typedef ratio<100, 1> hecto;
  typedef ratio<1000, 1> kilo;
  typedef ratio<1000000, 1> mega;
  typedef ratio<1000000000, 1> giga;

  typedef ratio<1000000000000LL, 1> tera;
  typedef ratio<1000000000000000LL, 1> peta;
  typedef ratio<1000000000000000000LL, 1> exa;
}