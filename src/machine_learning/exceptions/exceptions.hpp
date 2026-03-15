#pragma once

#include <string>
#include <stdexcept>
#include <fmt/format.h>

namespace network {
    namespace math {
        class LinearAlgebraException : public std::runtime_error {
        public:
            explicit LinearAlgebraException(const std::string& msg)
                : std::runtime_error(msg) {}
        };

        class DimensionMismatch : public LinearAlgebraException{
        public:
            explicit DimensionMismatch(const std::string& msg) 
                : LinearAlgebraException(fmt::format("Dimension mismatch: {}", msg)) {}
        };

        class OutOfBounds : public LinearAlgebraException {
        public:
            explicit OutOfBounds(const std::string& msg) 
                : LinearAlgebraException (fmt::format("Out of bounds: ", msg)) {}
        };
    } //namspace network::math

    namespace loader {
        class LoaderException : public std::runtime_error {
        public:
            explicit LoaderException(const std::string& msg)
                : std::runtime_error(msg) {}
        };

        class FileOpenException : public LoaderException {
        public:
            explicit FileOpenException(const std::string& path)
                : LoaderException(fmt::format("Failed to open file: {}", path)) {}
        };

        class FileReadException : public LoaderException {
        public:
            explicit FileReadException(const std::string& path)
                : LoaderException(fmt::format("Failed to read file: {}", path)) {}
        };
    } //namspace network::loader

    namespace activation {
        class UnsupportedActivationType : public std::runtime_error {
            public:
                explicit UnsupportedActivationType(const std::string& type)
                    : std::runtime_error(fmt::format("Unsupported activation type: {}", type)) {}
        };
    } //namspace network::activation
} // namespace network