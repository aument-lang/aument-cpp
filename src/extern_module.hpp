#pragma once

#include <aument.h>
#include <string_view>

namespace au {
namespace extern_module {

struct options {
  private:
    struct au_extern_module_options *c_options;

  public:
    options(struct au_extern_module_options *c_options)
        : c_options(c_options) {}
};

struct extern_module {
  private:
    au_extern_module_t c_module;

    extern_module(au_extern_module_t c_module) : c_module(c_module) {}

  public:
    extern_module() { c_module = au_extern_module_new(); }
    ~extern_module() {
        if (c_module != 0) {
            au_data_free(c_module);
            c_module = 0;
        }
    }

    static extern_module none() {
        extern_module m(0);
        return m;
    }

    au_extern_module_t into_c_module() {
        auto retval = c_module;
        c_module = nullptr;
        return retval;
    }

    void add_fn(const char *name, au_extern_func_t func, int num_args) {
        au_extern_module_add_fn(c_module, name, func, num_args);
    }
};

} // namespace extern_module
} // namespace au

// Replace our old C macro with the newer C++ macro
#undef AU_EXTERN_MODULE_MAIN

#define AU_EXTERN_MODULE_MAIN(OPTIONS_ID)                                 \
    static inline au::extern_module::extern_module                        \
        au_extern_module_load_impl(au::extern_module::options);           \
    extern "C" au_extern_module_t au_extern_module_load(                  \
        struct au_extern_module_options *options) {                       \
        return au_extern_module_load_impl(                                \
                   au::extern_module::options(options))                   \
            .into_c_module();                                             \
    }                                                                     \
    au::extern_module::extern_module au_extern_module_load_impl(          \
        au::extern_module::options OPTIONS_ID)

#define AU_EXTERN_MODULE_EXPORT(MODULE, FN_ID)                            \
    do {                                                                  \
        au::extern_module::extern_module &m = (MODULE);                   \
        m.add_fn(#FN_ID, AU_EXPORTED_##FN_ID##_impl,                      \
                 AU_EXPORTED_##FN_ID##_args);                             \
    } while (0)
