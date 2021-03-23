#pragma once

#include <aument.h>

namespace au {

struct value {
  private:
    au_value_t c_value;

  public:
    /// This function is internal and should not be used outside of library
    /// macros
    value(const au_value_t c_value) { this->c_value = c_value; }

    value() { c_value = au_value_none(); }
    ~value() {
        au_value_deref(c_value);
        c_value = au_value_none();
    }

    value(int32_t n) { c_value = au_value_int(n); }
    value(bool n) { c_value = au_value_bool(n ? 1 : 0); }
    value(double n) { c_value = au_value_double(n); }

    // copy ctor
    value(const value &rhs) {
        au_value_ref(rhs.c_value);
        c_value = rhs.c_value;
    }

    // move ctor
    value(value &&rhs) {
        c_value = rhs.c_value;
        rhs.c_value = au_value_none();
    }

    // operator= ctor
    value &operator=(const value &rhs) {
        au_value_ref(rhs.c_value);
        c_value = rhs.c_value;
        return *this;
    }

    /// Returns a nil value
    static value nil() {
        value v;
        return v;
    }

    /// This function is internal and should not be used outside of library
    /// macros
    au_value_t into_c_value() {
        auto retval = c_value;
        c_value = au_value_none();
        return retval;
    }
};

}; // namespace au