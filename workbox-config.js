module.exports = {
	globDirectory: 'dist/',
	globPatterns: [
		'**/*.{js,wasm,html,woff2,webmanifest}'
	],
	swDest: 'dist/sw.js',
	ignoreURLParametersMatching: [
		/^utm_/,
		/^fbclid$/
	]
};