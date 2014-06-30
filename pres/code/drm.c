int radeon_info_ioctl(struct drm_device *dev,
                      void *data,
                      struct drm_file *filp) {
	/*!npk userptr_fieldp data value*/
	struct drm_radeon_info *info = data;
	uint32_t *value_ptr = (uint32_t *)
                ((unsigned long)info->value);
        uint32_t value = *value_ptr;
        /* ... */
}
