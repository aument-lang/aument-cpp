#include <iostream>
#include <aument.hpp>

AU_EXPORT_FN(test0, args, 0) {
    std::cout << "hello world!\n";
    return au::value(10);
}

AU_EXPORT_FN(test1, args, 1) {
    return std::move(args.at(0));
}

AU_EXTERN_MODULE_MAIN(options) {
    au::extern_module::extern_module module;
    AU_EXTERN_MODULE_EXPORT(module, test0);
    AU_EXTERN_MODULE_EXPORT(module, test1);
    return module;
}