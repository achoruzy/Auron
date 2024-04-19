make:

build:
	echo "Building..."
	cmake --build .

conan_install:
	conan install . -sbuild_type=Debug -of=.conan/debug --build=missing

conan_profile:
	conan profile detect