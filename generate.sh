#!/bin/bash

ROOT_DIR="src/lib"

function to_class_name() {
    # Convert folder name to PascalCase (basic)
    echo "$1" | awk -F'/' '{print toupper(substr($NF,1,1)) substr($NF,2)}'
}

function get_parent_class() {
    local path="$1"
    local parent=$(dirname "$path")
    [ "$parent" == "$ROOT_DIR" ] && echo "" || to_class_name "$parent"
}

find "$ROOT_DIR" -type d | while read dir; do
    class_name=$(to_class_name "$dir")
    parent_class=$(get_parent_class "$dir")

    hpp_file="$dir/${class_name}.hpp"
    cpp_file="$dir/${class_name}.cpp"
    include_guard=$(echo "${class_name}_HPP" | tr '[:lower:]' '[:upper:]')

    # Generate .hpp
    cat > "$hpp_file" <<EOF
#ifndef ${include_guard}
#define ${include_guard}

#include <iostream>
using namespace std;

EOF

    if [ -n "$parent_class" ]; then
        echo "#include \"../${parent_class}.hpp\"" >> "$hpp_file"
        echo "" >> "$hpp_file"
        echo "class $class_name : public $parent_class {" >> "$hpp_file"
    else
        echo "class $class_name {" >> "$hpp_file"
    fi

    cat >> "$hpp_file" <<EOF
public:
    $class_name();
    virtual ~$class_name() {}

    virtual string getType() const = 0;
    virtual string getBenefits() const = 0;

    void printInfo();
};

#endif
EOF

    # Generate .cpp
    if [ ! -f "$cpp_file" ]; then
        cat > "$cpp_file" <<EOF
#include "${class_name}.hpp"

$class_name::$class_name() {
    // constructor implementation
}

void $class_name::printInfo() {
    cout << getType() << " | " << getBenefits() << endl;
}
EOF
    fi
done
