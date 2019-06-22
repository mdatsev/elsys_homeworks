Rails.application.routes.draw do
  resources :orders, path: '/11b_17_MartinDatsevorders'
  resources :clients
  resources :products
  root 'orders#index'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
