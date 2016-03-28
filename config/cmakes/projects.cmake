# Set global property of generated projects
if (MSVC)
  # Affect only for VS
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)