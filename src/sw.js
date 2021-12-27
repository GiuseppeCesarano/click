const cache_name = "click";
const content_to_cache = [
  "index.html",
  "click.js",
  "click.wasm ",
  "https://raw.githubusercontent.com/JetBrains/JetBrainsMono/master/fonts/webfonts/JetBrainsMono-Bold.woff2",
];

self.addEventListener("install", (e) => {
  e.waitUntil(
    (async () => {
      const cache = await caches.open(cache_name);
      await cache.addAll(content_to_cache);
    })()
  );
});

self.addEventListener("fetch", (e) => {
  e.respondWith(
    (async () => {
      const r = await caches.match(e.request);
      if (r) {
        return r;
      }
      const response = await fetch(e.request);
      const cache = await caches.open(cache_name);
      cache.put(e.request, response.clone());
      return response;
    })()
  );
});
