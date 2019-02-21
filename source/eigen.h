/*
 * eigen.h Serializers for dense matrices/arrays/vectors from Eigen.
 *
 * References:
 *
 *   [1]
 *
 * Future Improvements:
 *
 *   [1] 
 *
 * 
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-8 T Clark. All Rights Reserved.
 *
 */

#ifndef CPPLOT_EIGEN_H
#define CPPLOT_EIGEN_H

#include <Eigen/Dense>


namespace cpplot {


/** @brief A serialiser to convert dense eigen arrays to json objects using nlohmann::json
 *
 * Turns eigen array into a valid json array.
 *      1D arrays become lists:
 *          [24.23, 3.4, 8.4]
 *      2D arrays become lists of lists:
 *          [[24.23, 3.4, 8.4],[45.23, 5.4, 9.4]]
 *
 * TODO manage tensors for 3d volumetric plots
 *
 * Output is written as a row major array. So (assuming eigen's default settings for orientation), doing:
 *
 *   Eigen::ArrayXXd arr(5,2);
 *   arr << 0.0, 0.1,
 *          1.0, 1.1,
 *          2.0, 2.1,
 *          3.0, 3.1,
 *          4.0, 4.1;
 *   nlohmann::json j;
 *   to_json(j, arr);
 *   std::cout << "array element 0,1: " << arr(0,1) << std::endl;
 *   std::cout << "array element 1,0: " << arr(1,0) << std::endl;
 *   std::cout << j << std::endl;
 *
 * Prints:
 *
 *   array 0,1: 0.1
 *   array 1,0: 1
 *   [[0,0.1],[1,1.1],[2,2.1],[3,3.1],[4,4.1]]
 *
 * @tparam Derived The derived array or matrix type
 * @param j An nlohmann::json array
 * @param[in] in The matrix or array to serialise into json array
 */
template<typename Derived>
void to_json(nlohmann::json& j, const Eigen::DenseBase<Derived>& in) {

    // Use the eigen matrix formatting code to stream the matrix to a string.
    // This'll likely be faster than anything I can do here.
    Eigen::IOFormat vector_format(Eigen::FullPrecision, Eigen::DontAlignCols, ", ", ", ", "[", "]");
    Eigen::IOFormat matrix_format(Eigen::FullPrecision, Eigen::DontAlignCols, ", ", ", ", "[", "]", "[", "]");

    // Stream the eigen matrix, vector or array
    std::stringstream value_stream;
    if (in.cols() == 1 && in.rows() > 0) {
        value_stream << in.transpose().format(vector_format);
    } else if (in.rows() == 1) {
        value_stream << in.format(vector_format);
    } else {
        value_stream << in.format(matrix_format);
    }

    // Explicitly add the string as the json object
    // TODO - reparsing this string object is pretty inefficient. Maybe best to write my own after all
    j = nlohmann::json::parse(value_stream.str());

}


} // end namespace

#endif //CPPLOT_EIGEN_H
