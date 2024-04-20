make:
	

cmake_build:
	echo "Building..."
	cd Build && cmake ../
	cd Build && cmake --build .

conan_install:
	conan install . -sbuild_type=Debug -of=.conan/debug --build=missing

conan_profile:
	conan profile detect

run:
	./Build/Debug/Auron.exe