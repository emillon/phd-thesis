typedef unsigned long uint32_t;

struct drm_radeon_info {
    uint32_t *value;
};

int radeon_info_ioctl(struct drm_device *d, void *data,
        struct drm_file *f)
{
	/*!npk userptr_fieldp data value*/
	struct drm_radeon_info *info;
	uint32_t *value_ptr;
	uint32_t value;
	struct drm_crtc *crtc;
	int i, found;

	info = data;
	value_ptr = info->value;
        value = *value_ptr;      /* erreur */
        return 0;
}
