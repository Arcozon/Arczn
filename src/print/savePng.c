#include "arczn.h"

const char	*_getFName(const t_art *art) {
	static const char	format[] = "Arczn_%lux%lu_%02d-%02d-%02d:%02d:%02d";

	if (art->fName)
		return (art->fName);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("now: \n", );

	const int rLen = snprintf(NULL, 0, format, art->width, art->height, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	char *res = malloc(sizeof(char) * (rLen + 1));
	printf("%d\n", rLen);
	sprintf(res, format, art->width, art->height, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return (res);
}

void	printSavePng(const t_art *art) {
	const char	*fName = _getFName(art);	
	int			err = 0;
	FILE		*pngFile	= fopen(fName, "w+");
	spng_ctx	*ctx		= spng_ctx_new(SPNG_CTX_ENCODER);
	uint8_t		*buff		= NULL;
	struct spng_ihdr ihdr	= {0};

	if (!pngFile || !ctx)	goto err;

	ihdr.width = art->widthClr;
	ihdr.height = art->heightClr;
	ihdr.bit_depth = 8;
	if (sizeof(t_clr) == 3)			ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR;
	else if (sizeof(t_clr) == 4)	ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

	if ((err = spng_set_ihdr(ctx, &ihdr))) goto err;
	if ((err = spng_set_png_file(ctx, pngFile))) goto err;

	const size_t	bSize = art->widthClr * art->heightClr * sizeof(t_clr);
	buff = malloc(bSize);
	if (!buff)	goto err;

	const size_t	buffLineWidth = art->widthClr * sizeof(t_clr);
	for (size_t i = 0; i < art->heightClr; ++i)
		memcpy(buff + i * buffLineWidth, art->arrClr[i], buffLineWidth);
	
	if ((err = spng_encode_image(ctx, buff, bSize, SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE))) goto err;
	goto done;
	
	err:	fprintf(stderr, "Err(%d): %s\n", err, spng_strerror(err));
	done:
	fclose(pngFile);
	free(buff);
	spng_ctx_free(ctx);
}
