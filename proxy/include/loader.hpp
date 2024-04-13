#pragma once

namespace std::filesystem {
    class path;
}

bool is_current_process_compatible(std::filesystem::path &process_dir);
void load_alpha1(std::filesystem::path process_dir);