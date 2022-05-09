cmake_minimum_required(VERSION 3.16)
project(chain VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# compila sempre con i warning abilitati
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")

# richiedi il componente graphics della libreria SFML, versione 2.5
#   le dipendenze vengono identificate automaticamente
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# aggiungi l'eseguibile chain-sfml, da produrre a partire dai sorgenti indicati
#   notare l'assenza degli header file, che pero' possono essere indicati
add_executable(chain-sfml main.cpp chain.cpp ppstate.cpp)
# l'eseguibile dipende dalla libreria sfml-graphics e sue dipendenze
target_link_libraries(chain-sfml PRIVATE sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile chain.t, da produrre a partire dai sorgenti indicati
  add_executable(chain.t chain.test.cpp chain.cpp ppstate.cpp)
  target_link_libraries(chain.t PRIVATE sfml-graphics)
  # aggiungi l'eseguibile chain.t alla lista dei test, con nome chain.t
  add_test(NAME chain.t COMMAND chain.t)

endif()
