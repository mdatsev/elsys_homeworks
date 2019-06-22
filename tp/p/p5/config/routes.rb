Rails.application.routes.draw do
  resources :cinema_film_connections, path: '/11b_17_MartinDatsevfilms/'
  resources :cinemas
  resources :films
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
