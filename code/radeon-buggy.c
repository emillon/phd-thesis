/* from drivers/gpu/drm/radeon/radeon_kms.c */
int radeon_info_ioctl(struct drm_device *dev, void *data, struct drm_file *filp)
{
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_info *info;
	struct radeon_mode_info *minfo = &rdev->mode_info;
	uint32_t *value_ptr;
	uint32_t value;
	struct drm_crtc *crtc;
	int i, found;

	info = data;
	value_ptr = (uint32_t *)((unsigned long)info->value);
	value = *value_ptr;
	switch (info->request) {
	case RADEON_INFO_DEVICE_ID:
		value = dev->pci_device;
		break;
	case RADEON_INFO_NUM_GB_PIPES:
		value = rdev->num_gb_pipes;
		break;
	case RADEON_INFO_NUM_Z_PIPES:
		value = rdev->num_z_pipes;
		break;
	case RADEON_INFO_ACCEL_WORKING:
		/* xf86-video-ati 6.13.0 relies on this being false for evergreen */
		if ((rdev->family >= CHIP_CEDAR) && (rdev->family <= CHIP_HEMLOCK))
			value = false;
		else
			value = rdev->accel_working;
		break;
	case RADEON_INFO_CRTC_FROM_ID:
		for (i = 0, found = 0; i < rdev->num_crtc; i++) {
			crtc = (struct drm_crtc *)minfo->crtcs[i];
			if (crtc && crtc->base.id == value) {
				struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
				value = radeon_crtc->crtc_id;
				found = 1;
				break;
			}
		}
		if (!found) {
			DRM_DEBUG_KMS("unknown crtc id %d\n", value);
			return -EINVAL;
		}
		break;
	case RADEON_INFO_ACCEL_WORKING2:
		value = rdev->accel_working;
		break;
	case RADEON_INFO_TILING_CONFIG:
		if (rdev->family >= CHIP_CEDAR)
			value = rdev->config.evergreen.tile_config;
		else if (rdev->family >= CHIP_RV770)
			value = rdev->config.rv770.tile_config;
		else if (rdev->family >= CHIP_R600)
			value = rdev->config.r600.tile_config;
		else {
			DRM_DEBUG_KMS("tiling config is r6xx+ only!\n");
			return -EINVAL;
		}
	case RADEON_INFO_WANT_HYPERZ:
		mutex_lock(&dev->struct_mutex);
		if (rdev->hyperz_filp)
			value = 0;
		else {
			rdev->hyperz_filp = filp;
			value = 1;
		}
		mutex_unlock(&dev->struct_mutex);
		break;
	default:
		DRM_DEBUG_KMS("Invalid request %d\n", info->request);
		return -EINVAL;
	}
	if (DRM_COPY_TO_USER(value_ptr, &value, sizeof(uint32_t))) {
		DRM_ERROR("copy_to_user\n");
		return -EFAULT;
	}
	return 0;
}

/* from include/drm/radeon_drm.h */
struct drm_radeon_info {
	uint32_t		request;
	uint32_t		pad;
	uint64_t		value;
};

/* from drivers/gpu/drm/radeon/radeon_kms.c */
struct drm_ioctl_desc radeon_ioctls_kms[] = {
	/* KMS */
	DRM_IOCTL_DEF(DRM_RADEON_INFO, radeon_info_ioctl, DRM_AUTH|DRM_UNLOCKED)
};

/* from drivers/gpu/drm/radeon/radeon_drv.c */

static struct drm_driver kms_driver = {
	.driver_features =
	    DRIVER_USE_AGP | DRIVER_USE_MTRR | DRIVER_PCI_DMA | DRIVER_SG |
	    DRIVER_HAVE_IRQ | DRIVER_HAVE_DMA | DRIVER_IRQ_SHARED | DRIVER_GEM,
	.dev_priv_size = 0,
	.ioctls = radeon_ioctls_kms,
	.name = "radeon",
	.desc = "ATI Radeon",
	.date = "20080528",
	.major = 2,
	.minor = 6,
	.patchlevel = 0,
};

/* from drivers/gpu/drm/drm_drv.c */
int drm_init(struct drm_driver *driver)
{
	DRM_DEBUG("\n");
	INIT_LIST_HEAD(&driver->device_list);

	if (driver->driver_features & DRIVER_USE_PLATFORM_DEVICE)
		return drm_platform_init(driver);
	else
		return drm_pci_init(driver);
}
