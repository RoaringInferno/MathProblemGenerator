## Notes
Conflicting settings, when both enabled, will both be treated as false.

## Developer Notes
### Adding a New Process
1. Add a new header file in `lib/generate/include/generate/`, copying from an existing header. Rename the namespace to the internal name for the process, `<process_name>`. Change `generate::<process_name>::parameters`'s declaration to reflect the mutable parameters of the process.
2. Add the header's filename to `lib/generate/include/generate/all-inc.hpp`.
3. Write the logic for the `mprgen::MathProblem generate::<process_name>::problem(const parameters&)` function to reflect the process's logic. Copy-paste in the definition for `void generate::<process_name>::problem_set(const parameters&, const iterator_range_t&)` from an existing header.
4. Add a `process` enum and `PROCESS_SIGNATURE` signature to `include/input-parsing.hpp` and update the hash function to add it as a branch.
5. Add to the switch case in `src/daemon_spawn_process.cpp`, using the other cases as reference.
6. Make a section in the settings map in `src/daemon_settings.cpp`, and fill in the settings for the process.
7. Add a profiling section to `profiling/main.cpp`. Run it and set the threading threshold accordingly.