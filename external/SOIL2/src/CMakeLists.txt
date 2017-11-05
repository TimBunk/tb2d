# SOLI2

set(SOILSOURCE
SOIL2/etc1_utils.c
SOIL2/etc1_utils.h
SOIL2/image_DXT.c
SOIL2/image_DXT.h
SOIL2/image_helper.c
SOIL2/image_helper.h
SOIL2/jo_jpeg.h
SOIL2/pkm_helper.h
SOIL2/pvr_helper.h
SOIL2/SOIL2.c
SOIL2/SOIL2.h
SOIL2/stb_image_write.h
SOIL2/stb_image.h
SOIL2/stbi_DDS_c.h
SOIL2/stbi_DDS.h
SOIL2/stbi_ext_c.h
SOIL2/stbi_ext.h
SOIL2/stbi_pkm_c.h
SOIL2/stbi_pkm.h
SOIL2/stbi_pvr_c.h
SOIL2/stbi_pvr.h
)

SET (LIB_TYPE STATIC)

# Create a library from the source of SOIL2

add_library (SOIL2 ${LIB_TYPE} ${SOILSOURCE})