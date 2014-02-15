/* drivers/gpu/drm/radeon/radeon_kms.c */
int radeon_info_ioctl(struct drm_device *dev, void *data,
                      struct drm_file *filp) {
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_info *info;
	struct radeon_mode_info *minfo = &rdev->mode_info;
	uint32_t *value_ptr;
	uint32_t value;
	struct drm_crtc *crtc;
	int i, found;

	info = data;
	value_ptr = (uint32_t *) ((unsigned long)info->value);
/*=>*/  value = *value_ptr;
        /* ... */
}
