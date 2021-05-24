packages := $(shell ls src)
out_packages := $(addprefix _build/,$(packages))
jar_files := $(addsuffix .jar,$(out_packages))
input = ../helloworld.bf

define one_file
_build/$1.class: src/$1.java
	@cd src && javac $1.java -d ../_build
endef

define one_package
$(foreach file,$(basename $(shell ls src/$1)),$(eval $(call one_file,$1/$(file))))

_build/$1.jar: $(addsuffix .class,$(addprefix _build/$1/,$(basename $(shell ls src/$1))))
	@cd _build && jar -uvfM $1.jar $1/*.class
endef

$(foreach package,$(packages),$(eval $(call one_package,$(package))))

build: $(jar_files)
	@echo "build complete."

run: $(jar_files)
	@cd _build && java app.App $(abspath $(input))

.PHONY: run build