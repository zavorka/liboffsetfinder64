//
//  exception.cpp
//  liboffsetfinder64
//
//  Created by tihmstar on 09.03.18.
//  Copyright © 2018 tihmstar. All rights reserved.
//

#include "exception.hpp"
#include "all_liboffsetfinder.hpp"
#include <string>

using namespace tihmstar;

exception::exception(int code, std::string err, std::string filename) :
    _err(err),
    _code(code),
    _build_commit_count(OFFSETFINDER64_VERSION_COMMIT_COUNT),
    _build_commit_sha(OFFSETFINDER64_VERSION_COMMIT_SHA),
    _filename(filename){};

const char *exception::what(){
    return _err.c_str();
}

int exception::code() const{
    return _code | (int)(_filename.size()<<16);
}

const std::string& exception::build_commit_count() const {
    return _build_commit_count;
};

const std::string& exception::build_commit_sha() const {
    return _build_commit_sha;
};

out_of_range::out_of_range(std::string err) : exception(__LINE__, err, "exception.cpp"){};

symbol_not_found::symbol_not_found(int code, std::string sym, std::string filename) : exception(code,{"failed to find symbol: " + sym},filename) {};

load_command_not_found::load_command_not_found(int code, int cmd, std::string filename) : exception(code,{"failed to find cmd: " + std::to_string(cmd)},filename), _cmd(cmd) {};
int load_command_not_found::cmd() const { return _cmd;};

symtab_not_found::symtab_not_found(int code, std::string err, std::string filename) : exception(code,err,filename) {};

limit_reached::limit_reached(int code, std::string err, std::string filename) : exception(code,err,filename) {};

bad_branch_destination::bad_branch_destination(int code, std::string err, std::string filename) : exception(code,err,filename) {};

