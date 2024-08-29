#include "daemon.hpp"

#include "generate/all-problems.hpp"

#include <string>
#include <string_view>

#define EXECUTE_PROCESS(PROBLEM_NMSP)                                                                   \
if (should_thread(process_signature, problem_count))                                                    \
{                                                                                                       \
    spawns.push_back(std::thread(generate::PROBLEM_NMSP::problem_set, params, spawn_range));            \
}                                                                                                       \
else                                                                                                    \
{                                                                                                       \
    generate::PROBLEM_NMSP::problem_set(params, spawn_range);                                           \
}

void Daemon::spawn_process(std::string_view process_signature)
{
    const auto pull_int_setting = [&](const std::string& setting_name) -> Daemon_settings::int_value_t
    {
        return settings.get_int_setting(PROCESS_SIGNATURE[process::polynomial_factoring] + setting_name);
    };


    ProcessStringHash process_hash(process_signature);
    generate::problem_count_t problem_count = settings.get_int_setting("problem-count");
    generate::iterator_range_t spawn_range = generate_spawn_range(problem_count);


    settings.print_verbose("Generating " + std::to_string(problem_count) + " \"" + std::string(process_signature) + "\" problem(s) with settings...");
    switch (process_hash.value())
    /**
     * For each process, generate the config struct.
     * Then, if the process is not forced into series and it is above the threading threshold for the particular process, add it to the spawns vector.
     * Otherwise, call the function in series.
     */
    {
        case process::polynomial_factoring:
        {
            const generate::polynomial_factoring::parameters params = {
                settings.get_int_setting("polyfac-factor-max"),
                settings.get_int_setting("polyfac-factor-min"),
                settings.get_int_setting("polyfac-front-factor-max"),
                settings.get_int_setting("polyfac-front-factor-min"),
                static_cast<generate::polynomial_factoring::factor_count_t>(settings.get_int_setting("polyfac-factor-count"))
            };
            settings.print_verbose("\tfactor-count = " + std::to_string(params.factor_count));
            settings.print_verbose("\tfront-factor-min = " + std::to_string(params.front_factor_min));
            settings.print_verbose("\tfront-factor-max = " + std::to_string(params.front_factor_max));
            settings.print_verbose("\tfactor-min = " + std::to_string(params.factor_min));
            settings.print_verbose("\tfactor-max = " + std::to_string(params.factor_max));

            EXECUTE_PROCESS(polynomial_factoring)
            return;
        }
        case process::dot_product:
        {
            const generate::dot_product::parameters params = {
                settings.get_int_setting("dotprod-component-max"),
                settings.get_int_setting("dotprod-component-min"),
                static_cast<generate::dot_product::vector_dimension_t>(settings.get_int_setting("dotprod-vector-dimension"))
            };
            settings.print_verbose("\tcomponent-max = " + std::to_string(params.component_max));
            settings.print_verbose("\tcomponent-min = " + std::to_string(params.component_min));
            settings.print_verbose("\tvector-dimension = " + std::to_string(params.vector_dimension));

            EXECUTE_PROCESS(dot_product)
            return;
        }
        case process::cross_product:
        {
            const generate::cross_product::parameters params = {
                settings.get_int_setting("crossprod-component-max"),
                settings.get_int_setting("crossprod-component-min"),
            };
            settings.print_verbose("\tcomponent-max = " + std::to_string(params.component_max));
            settings.print_verbose("\tcomponent-min = " + std::to_string(params.component_min));

            EXECUTE_PROCESS(cross_product)
            return;
        }
        case process::matrix_multiplication:
        {
            const generate::matrix_multiplication::parameters params = {
                settings.get_int_setting("matrix-mult-max-result-rows"),
                settings.get_int_setting("matrix-mult-min-result-rows"),
                settings.get_int_setting("matrix-mult-max-shared-dim"),
                settings.get_int_setting("matrix-mult-min-shared-dim"),
                settings.get_int_setting("matrix-mult-max-result-cols"),
                settings.get_int_setting("matrix-mult-min-result-cols"),
                settings.get_int_setting("matrix-mult-max-cell-value"),
                settings.get_int_setting("matrix-mult-min-cell-value")
            };
            settings.print_verbose("\tmatrix-mult-max-result-rows = "  + std::to_string(params.max_result_rows));
            settings.print_verbose("\tmatrix-mult-min-result-rows = "  + std::to_string(params.min_result_rows));
            settings.print_verbose("\tmatrix-mult-max-shared-dim = "  + std::to_string(params.max_shared_dim));
            settings.print_verbose("\tmatrix-mult-min-shared-dim = "  + std::to_string(params.min_shared_dim));
            settings.print_verbose("\tmatrix-mult-max-result-cols = "  + std::to_string(params.max_result_cols));
            settings.print_verbose("\tmatrix-mult-min-result-cols = "  + std::to_string(params.min_result_cols));
            settings.print_verbose("\tmatrix-mult-max-cell-value = "  + std::to_string(params.max_cell_value));
            settings.print_verbose("\tmatrix-mult-min-cell-value = "  + std::to_string(params.min_cell_value));

            EXECUTE_PROCESS(matrix_multiplication)
            return;
        }
    };
}

#undef EXECUTE_PROCESS