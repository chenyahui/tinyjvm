//
// Created by cyhone on 18-5-7.
//

#ifndef TOYJVM_STRING_POOL_H
#define TOYJVM_STRING_POOL_H

#include <toyjvm/utilities/modified_utf8.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/utilities/all_static.h>
#include <unordered_map>

namespace jvm {
    struct ModifiedUTF8Hasher {
        size_t operator()(ModifiedUTF8 const &c) const
        {
            const auto &data = c.rawUTF8();
            return boost::hash_range(data.begin(), data.end());
        }
    };

    std::string javaLangStringAsString(jobj str_obj);

    class StringPool : AllStatic {
    public:
        static jobj intern(ModifiedUTF8 &&);

    private:
        static std::unordered_map<ModifiedUTF8, jobj, ModifiedUTF8Hasher> inner_str_objects;
    };
}
#endif //TOYJVM_STRING_POOL_H
